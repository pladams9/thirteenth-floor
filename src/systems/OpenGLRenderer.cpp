/**
 * OpenGLRenderer.cpp
 *
 */

#include "systems/OpenGLRenderer.h"


/* INCLUDES */
#include <array>
#include <chrono>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "components/Camera.h"
#include "components/CameraTargetPosition.h"
#include "components/MeshDrawable.h"
#include "components/Transform.h"
#include "components/VoxelDrawable.h"
#include "components/Voxels.h"
#include "components/LightSource.h"
#include "engine/Engine.h"
#include "Logger.h"
#include "Drawable.h"


namespace TF
{
namespace Sys
{


/* METHOD DEFINITIONS */
OpenGLRenderer::OpenGLRenderer(Engine* engine, int win_width, int win_height)
: System(engine)
{
	_engine->RegisterFrameEndCallback
	(
			[this]() { this->Step(); }
	);

	// Initialize GLEW
	glewInit();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// Setup View & Projection Matrices
	_view = glm::mat4(1.0f);
	_viewPos = glm::vec3(0.0f);
	_projection = glm::perspective(glm::radians(45.0f), (float)win_width / float(win_height), 0.5f, 500.0f);
}

void OpenGLRenderer::Step()
{
	UpdateView();
	UpdateLights();
	Render();
}


void OpenGLRenderer::Render()
{
	// Clear
	glClearColor(0.02, 0.05, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw voxel groups
	for(Entity entity : _engine->GetEntities({"Voxels", "VoxelDrawable", "Transform"}))
	{
		DrawVoxels(
				static_cast<Comp::Voxels*>(entity["Voxels"]),
				static_cast<Comp::VoxelDrawable*>(entity["VoxelDrawable"]),
				static_cast<Comp::Transform*>(entity["Transform"])
		);
	}

	// Draw single meshes
	for(Entity entity : _engine->GetEntities({"MeshDrawable", "Transform"}))
	{
		DrawMesh(
				static_cast<Comp::MeshDrawable*>(entity["MeshDrawable"]),
				static_cast<Comp::Transform*>(entity["Transform"])
		);
	}
}

void OpenGLRenderer::UpdateView()
{
	std::vector<Entity> cameras = _engine->GetEntities({"Camera", "Transform"}, {"CameraTargetPosition"});
	Entity active_camera;
	bool camera_exists = false;
	for(Entity camera : cameras)
	{
		if(static_cast<Comp::Camera*>(camera["Camera"])->IsActive())
		{
			active_camera = camera;
			camera_exists = true;
			break;
		}
	}
	if(!camera_exists) return;

	Comp::Transform* camera_transform = static_cast<Comp::Transform*>(active_camera["Transform"]);
	Util::vec3d cam_pos = camera_transform->GetPosition();
	glm::vec3 cameraPos = glm::vec3(cam_pos.x, cam_pos.y, cam_pos.z);
	_viewPos = cameraPos;

	if(active_camera["CameraTargetPosition"])
	{
		// Camera with target
		Comp::CameraTargetPosition* target_position =
				static_cast<Comp::CameraTargetPosition*>(active_camera["CameraTargetPosition"]);
		Util::vec3d target_pos = target_position->GetPosition();
		glm::vec3 targetPos = glm::vec3(target_pos.x, target_pos.y, target_pos.z);
		_view = glm::lookAt(
				cameraPos,
				glm::vec3(targetPos.x, targetPos.y, targetPos.z),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
	else
	{
		// Standard camera
		Util::vec3d cam_rot = camera_transform->GetRotation();
		glm::vec3 cameraDir;
		cameraDir.x = cos(cam_rot.pitch) * cos(cam_rot.yaw);
		cameraDir.y = sin(cam_rot.pitch);
		cameraDir.z = cos(cam_rot.pitch) * sin(cam_rot.yaw);
		cameraDir = glm::normalize(cameraDir);
		_view = glm::lookAt(
				cameraPos,
				cameraPos + cameraDir,
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
}

void OpenGLRenderer::UpdateLights()
{
	std::vector<Comp::Light> lights;
	for(Entity entity : _engine->GetEntities({"LightSource"}))
	{
		lights.push_back(static_cast<Comp::LightSource*>(entity["LightSource"])->GetLight());
	}
	_lights = lights;
}

void OpenGLRenderer::DrawMesh(Comp::MeshDrawable* meshDrawable, Comp::Transform* transform)
{
	Util::Drawable drawable = meshDrawable->GetDrawable();

	OpenGL::SingleModel model = _models.GetSingleModel(drawable.modelName);
	glBindVertexArray(model.VAO);

	_shaders.Use(drawable.shaderName);

	// Set Material
	_shaders.SetUniformVec3f("material.ambient", drawable.material.ambient);
	_shaders.SetUniformVec3f("material.diffuse", drawable.material.diffuse);
	_shaders.SetUniformVec3f("material.specular", drawable.material.specular);
	_shaders.SetUniformFloat("material.rough", drawable.material.rough);

	// Set Lights

	// Set viewPos
	_shaders.SetUniformVec3f("viewPos", _viewPos);

	// Set Matrices
	glm::mat4 model_matrix = MatrixFromTransform(transform);

	_shaders.SetUniformMat4f("model", model_matrix);
	_shaders.SetUniformMat4f("view", _view);
	_shaders.SetUniformMat4f("projection", _projection);

	// Draw Call
	glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);

	// Unbind VAO
	glBindVertexArray(0);
}

void OpenGLRenderer::DrawVoxels(Comp::Voxels* voxels, Comp::VoxelDrawable* voxelDrawable, Comp::Transform* transform)
{
	for(auto vd_pair : voxelDrawable->GetDrawables())
	{
		VoxelType voxel_type = vd_pair.first;
		Util::Drawable drawable = vd_pair.second;

		// Update instances
		if(voxels->HasBeenUpdated(voxel_type))
		{
			std::vector<Voxel> v_list = voxels->GetVoxels(voxel_type);
			std::vector<float> verts;
			for(Voxel v : v_list)
			{
				verts.push_back(v.position.x);
				verts.push_back(v.position.y);
				verts.push_back(v.position.z);
			}
			_models.UpdateInstances(drawable.modelName, voxel_type, verts, voxelDrawable->GetVoxelScale());
			voxels->ClearUpdateFlag(voxel_type);
		}

		OpenGL::InstancedModel model = _models.GetInstancedModel(drawable.modelName, voxel_type);
		glBindVertexArray(model.VAO);

		_shaders.Use(drawable.shaderName);

		// Set Material
		_shaders.SetUniformVec3f("material.ambient", drawable.material.ambient);
		_shaders.SetUniformVec3f("material.diffuse", drawable.material.diffuse);
		_shaders.SetUniformVec3f("material.specular", drawable.material.specular);
		_shaders.SetUniformFloat("material.rough", drawable.material.rough);

		// Set Lights
		const int NUM_DIR_LIGHTS = 2;
		const int NUM_POINT_LIGHTS = 4;
		int cur_dir_light = 0;
		int cur_point_light = 0;
		for(Comp::Light l : _lights)
		{
			if((l.lightType == Comp::DIRECTIONAL) && (cur_dir_light < NUM_DIR_LIGHTS))
			{
				std::stringstream name;
				name << "dirLights[" << cur_dir_light << "].";

				_shaders.SetUniformVec3f(name.str() + "ambient", l.ambient);
				_shaders.SetUniformVec3f(name.str() + "diffuse", l.diffuse);
				_shaders.SetUniformVec3f(name.str() + "specular", l.specular);
				_shaders.SetUniformVec3f(name.str() + "direction", l.direction);

				cur_dir_light++;
			}
			if((l.lightType == Comp::POINT) && (cur_point_light < NUM_POINT_LIGHTS))
			{
				std::stringstream name;
				name << "pointLights[" << cur_point_light << "].";

				_shaders.SetUniformVec3f(name.str() + "ambient", l.ambient);
				_shaders.SetUniformVec3f(name.str() + "diffuse", l.diffuse);
				_shaders.SetUniformVec3f(name.str() + "specular", l.specular);
				_shaders.SetUniformVec3f(name.str() + "position", l.position);
				_shaders.SetUniformFloat(name.str() + "constant", l.constant);
				_shaders.SetUniformFloat(name.str() + "linear", l.linear);
				_shaders.SetUniformFloat(name.str() + "quadratic", l.quadratic);

				cur_point_light++;
			}
		}
		for(; cur_dir_light < NUM_DIR_LIGHTS; ++cur_dir_light)
		{
			std::stringstream name;
			name << "dirLights[" << cur_dir_light << "].";

			_shaders.SetUniformVec3f(name.str() + "ambient", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "diffuse", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "specular", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "direction", Util::vec3f(0,0,0));
		}
		for(; cur_point_light < NUM_POINT_LIGHTS; ++cur_point_light)
		{
			std::stringstream name;
			name << "pointLights[" << cur_point_light << "].";

			_shaders.SetUniformVec3f(name.str() + "ambient", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "diffuse", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "specular", Util::vec3f(0,0,0));
			_shaders.SetUniformVec3f(name.str() + "position", Util::vec3f(0,0,0));
			_shaders.SetUniformFloat(name.str() + "constant", 1.0);
			_shaders.SetUniformFloat(name.str() + "linear", 0.09);
			_shaders.SetUniformFloat(name.str() + "quadratic", 0.032);
		}

		// Set Matrices
		glm::mat4 model_matrix = MatrixFromTransform(transform);

		_shaders.SetUniformMat4f("model", model_matrix);
		_shaders.SetUniformMat4f("view", _view);
		_shaders.SetUniformMat4f("projection", _projection);

		// Draw Call
		glDrawArrays(GL_TRIANGLES, 0, model.vertexCount * model.instanceCount);

		// Unbind VAO
		glBindVertexArray(0);
	}
}

glm::mat4 OpenGLRenderer::MatrixFromTransform(const Comp::Transform* transform)
{
	glm::mat4 output_matrix = glm::mat4(1.0f);
	Util::vec3d position = transform->GetPosition();
	Util::vec3d rotation = transform->GetRotation();
	Util::vec3d scale = transform->GetScale();

	output_matrix = glm::translate(output_matrix, glm::vec3(position.x, position.y, position.z));
	output_matrix = glm::rotate(output_matrix, (float)rotation.yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	output_matrix = glm::rotate(output_matrix, (float)rotation.pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	output_matrix = glm::rotate(output_matrix, (float)rotation.roll, glm::vec3(0.0f, 0.0f, 1.0f));
	output_matrix = glm::scale(output_matrix, glm::vec3(scale.x, scale.y, scale.z));

	return output_matrix;
}


}
}
