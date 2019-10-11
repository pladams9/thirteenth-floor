/*
 * graphics.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#include <systems/OpenGLRenderer.h>


/* INCLUDES */
#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/Camera.h"
#include <components/CameraTargetPosition.h>
#include <components/Shader.h>
#include <components/ModelName.h>
#include <components/Transform.h>
#include <engine/Engine.h>
#include "Logger.h"


namespace TF
{
namespace Sys
{


/* METHOD DEFINITIONS */
OpenGLRenderer::OpenGLRenderer(Engine* engine, int win_width, int win_height)
: System(engine)
{
	this->engine->RegisterFrameEndCallback
	(
			[this]() { this->Step(); }
	);

	// Initialize GLEW
	glewInit();

	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_CULL_FACE);

	// Setup View & Projection Matrices
	this->view = glm::mat4(1.0f);
	this->projection = glm::perspective(glm::radians(45.0f), (float)win_width / float(win_height), 1.0f, 500.0f);
}

void OpenGLRenderer::Step()
{
	this->UpdateView();
	this->Render();
}


void OpenGLRenderer::Render()
{
	// Clear
	glClearColor(0.02, 0.05, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	for(Entity entity : this->engine->GetEntities({"ModelName", "Shader", "Transform"}))
	{
		this->DrawEntity(
				static_cast<Comp::ModelName*>(entity["ModelName"]),
				static_cast<Comp::Shader*>(entity["Shader"]),
				static_cast<Comp::Transform*>(entity["Transform"])
		);
	}

	// Swap buffers

}

void OpenGLRenderer::UpdateView()
{
	std::vector<Entity> cameras = this->engine->GetEntities({"Camera", "Transform"}, {"CameraTargetPosition"});
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

	if(active_camera["CameraTargetPosition"])
	{
		// Camera with target
		Comp::CameraTargetPosition* target_position =
				static_cast<Comp::CameraTargetPosition*>(active_camera["CameraTargetPosition"]);
		Util::vec3d target_pos = target_position->GetPosition();
		glm::vec3 targetPos = glm::vec3(target_pos.x, target_pos.y, target_pos.z);
		this->view = glm::lookAt(
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
		this->view = glm::lookAt(
				cameraPos,
				cameraPos + cameraDir,
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
}


void OpenGLRenderer::DrawEntity(Comp::ModelName* modelComp, Comp::Shader* shaderComp, Comp::Transform* transform)
{
	// Get Model
	OpenGL::Model model = this->models.GetModel(modelComp->GetName());
	// Set VAO
	glBindVertexArray(model.VAO);

	// Set shader
	this->shaders.Use(shaderComp->GetName());

	// Set Matrices
	glm::mat4 model_matrix = glm::mat4(1.0f);
	Util::vec3d pos = transform->GetPosition();
	Util::vec3d rotation = transform->GetRotation();
	Util::vec3d scale = transform->GetScale();

	model_matrix = glm::translate(model_matrix, glm::vec3(pos.x, pos.y, pos.z));
	model_matrix = glm::rotate(model_matrix, (float)rotation.yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, (float)rotation.pitch, glm::vec3(1.0f, 0.0f, 0.0f));
	model_matrix = glm::rotate(model_matrix, (float)rotation.roll, glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, glm::vec3(scale.x, scale.y, scale.z));

	shaders.SetUniformMat4f("model", model_matrix);
	shaders.SetUniformMat4f("view", this->view);
	shaders.SetUniformMat4f("projection", this->projection);

	// Draw Call
	glDrawArrays(GL_TRIANGLES, 0, model.count);

	// Unbind VAO
	glBindVertexArray(0);
}


}
}
