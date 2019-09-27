/*
 * graphics.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#include <components/shaderComp.h>
#include <components/transformComps.h>
#include <components/vertexListComp.h>
#include <components/cameraTarget.h>
#include <iostream>
#include <array>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine.h>
#include <systems/graphics.h>


namespace TF
{


/* METHOD DEFINITIONS */
Graphics::Graphics(Engine* engine, int win_width, int win_height, std::string win_title)
: System(engine)
{
	// Setup OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	// Create window & OpenGL context
	this->window = SDL_CreateWindow(
			"Window Title",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			win_width, win_height,
			SDL_WINDOW_OPENGL
	);
	this->context = SDL_GL_CreateContext(this->window);

	// Initialize GLEW
	glewInit();
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Setup View & Projection Matrices
	this->view = glm::mat4(1.0f);

	this->projection = glm::perspective(glm::radians(45.0f), (float)win_width / float(win_height), 0.1f, 100.0f);
}

Graphics::~Graphics()
{
	// Clean up
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
}

void Graphics::Step()
{
	this->UpdateCamera();
	this->Render();
}

void Graphics::Render()
{
	// Clear
	glClearColor(0.1, 0.1, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	for(Entity entity : this->engine->GetEntities({"VertexListComp", "ShaderComp", "PositionComp", "ScaleComp", "RotationComp"}))
	{
		this->DrawEntity(
				dynamic_cast<VertexListComp*>(entity.second.at("VertexListComp")),
				dynamic_cast<ShaderComp*>(entity.second.at("ShaderComp")),
				dynamic_cast<PositionComp*>(entity.second.at("PositionComp")),
				dynamic_cast<ScaleComp*>(entity.second.at("ScaleComp")),
				dynamic_cast<RotationComp*>(entity.second.at("RotationComp"))
		);
	}

	// Swap buffers
	SDL_GL_SwapWindow(this->window);
}

void Graphics::UpdateCamera()
{
	/* Cameras with a target
	std::vector<Entity> cameras = this->engine->GetEntities({"PositionComp", "CameraTargetPosComp"});
	if(cameras.size() > 0)
	{
		Entity cam = cameras[0]; // Just take the first one found; TODO: deal with multiple cameras
		std::array<float, 3> cam_pos = dynamic_cast<PositionComp*>(cam.second.at("PositionComp"))->GetPosition();
		std::array<float, 3> cam_target_pos = dynamic_cast<CameraTargetPosComp*>(cam.second.at("CameraTargetPosComp"))->GetPosition();
		this->view = glm::lookAt(
				glm::vec3(cam_pos[0], cam_pos[1], cam_pos[2]),
				glm::vec3(cam_target_pos[0], cam_target_pos[1], cam_target_pos[2]),
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}*/

	// Cameras with a direction
	std::vector<Entity> cameras = this->engine->GetEntities({"PositionComp", "DirectionComp"});
	if(cameras.size() > 0)
	{
		Entity cam = cameras[0]; // Just take the first one found; TODO: deal with multiple cameras
		std::array<float, 3> cam_pos = dynamic_cast<PositionComp*>(cam.second.at("PositionComp"))->GetPosition();
		std::array<float, 3> cam_dir = dynamic_cast<DirectionComp*>(cam.second.at("DirectionComp"))->GetDirection();
		glm::vec3 cameraPos = glm::vec3(cam_pos[0], cam_pos[1], cam_pos[2]);
		glm::vec3 cameraDir = glm::vec3(cam_dir[0], cam_dir[1], cam_dir[2]);
		this->view = glm::lookAt(
				cameraPos,
				cameraPos + cameraDir,
				glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
}

void Graphics::DrawEntity(VertexListComp* vertComp, ShaderComp* shaderComp, PositionComp* posComp, ScaleComp* scaleComp, RotationComp* rotComp)
{
	// Set VAO
	glBindVertexArray(vertComp->GetVAO());

	// Set shader
	glUseProgram(shaderComp->GetProgram());

	// Set Matrices
	glm::mat4 model = glm::mat4(1.0f);
	std::array<float, 3> pos = posComp->GetPosition();
	std::array<float, 3> scale = scaleComp->GetScale();
	std::array<float, 3> r_axis = rotComp->GetRotationAxis();
	model = glm::translate(model, glm::vec3(pos[0], pos[1], pos[2]));
	model = glm::rotate(model, rotComp->GetRotation(), glm::vec3(r_axis[0], r_axis[1], r_axis[2]));
	model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]));
	int modelLoc = glGetUniformLocation(shaderComp->GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	int viewLoc = glGetUniformLocation(shaderComp->GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(this->view));

	int projectionLoc = glGetUniformLocation(shaderComp->GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(this->projection));


	// Draw Call
	glDrawElements(GL_TRIANGLES, vertComp->GetElementCount(), GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);
}


}
