/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <engine.h>

SDL_Window* Engine::window;
SDL_GLContext Engine::context;

void Engine::Init()
{
	// Setup
	glewInit();

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Engine::window = SDL_CreateWindow(
			"Window Title",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			640, 480,
			SDL_WINDOW_OPENGL
	);
	Engine::context = SDL_GL_CreateContext(window);
	SDL_GL_SetSwapInterval(1);
}

void Engine::Render()
{
	// Render
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(Engine::window);
}


void Engine::Cleanup()
{
	// Clean up
	SDL_GL_DeleteContext(Engine::context);
	SDL_DestroyWindow(Engine::window);
	SDL_Quit();
}
