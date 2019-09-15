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

#include <graphics_component.h>


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
}

Graphics::~Graphics()
{
	// Clean up
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Graphics::AddComponent(std::vector<float> vertices, std::vector<unsigned int> elements, const char* vertexShader, const char* fragmentShader)
{
	GraphicsComponent* gc = new GraphicsComponent;
	gc->UpdateVertices(vertices);
	gc->UpdateElements(elements, 6);
	gc->LoadShader(vertexShader, fragmentShader);
	this->gfxComps.push_back(gc);
}

void Graphics::Render()
{
	// Clear
	glClearColor(0.1, 0.1, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw components
	for(std::vector<GraphicsComponent*>::iterator it = this->gfxComps.begin(); it != this->gfxComps.end(); ++it)
	{
		(*it)->Draw();
	}

	// Swap
	SDL_GL_SwapWindow(this->window);
}


}
