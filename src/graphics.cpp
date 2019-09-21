/*
 * graphics.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#include <graphics.h>


/* INCLUDES */
#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine.h>
#include <shaderComp.h>
#include <vertexListComp.h>
#include <transformComps.h>


namespace TF
{


/* METHOD DEFINITIONS */
Graphics::Graphics()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

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
			640, 480,
			SDL_WINDOW_OPENGL
	);
	this->context = SDL_GL_CreateContext(this->window);

	// Initialize GLEW
	glewInit();
	glEnable(GL_DEPTH_TEST);
}

Graphics::~Graphics()
{
	// Clean up
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Graphics::Render()
{
	// Clear
	glClearColor(0.1, 0.1, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw components
	std::vector<std::string> types = {"VertexListComp", "ShaderComp", "PositionComp", "RotationComp"};
	for(std::vector<Component*> entity : this->engine->GetComponents(types))
	{
		this->DrawEntity(
				dynamic_cast<VertexListComp*>(entity[0]),
				dynamic_cast<ShaderComp*>(entity[1]),
				dynamic_cast<PositionComp*>(entity[2]),
				dynamic_cast<RotationComp*>(entity[3])
		);
	}

	// Swap
	SDL_GL_SwapWindow(this->window);
}

void Graphics::DrawEntity(VertexListComp* vertComp, ShaderComp* shaderComp, PositionComp* posComp, RotationComp* rotComp)
{
	// Set VAO
	glBindVertexArray(vertComp->GetVAO());

	// Set shader
	glUseProgram(shaderComp->GetProgram());

	// Set Matrices
	glm::mat4 model = glm::mat4(1.0f);
	std::array<float, 3> pos = posComp->GetPosition();
	std::array<float, 3> r_axis = rotComp->GetRotationAxis();
	model = glm::translate(model, glm::vec3(pos[0], pos[1], pos[2]));
	model = glm::rotate(model, rotComp->GetRotation(), glm::vec3(r_axis[0], r_axis[1], r_axis[2]));
	int modelLoc = glGetUniformLocation(shaderComp->GetProgram(), "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	int viewLoc = glGetUniformLocation(shaderComp->GetProgram(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
	int projectionLoc = glGetUniformLocation(shaderComp->GetProgram(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	// Draw Call
	glDrawElements(GL_TRIANGLES, vertComp->GetElementCount(), GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);
}


}
