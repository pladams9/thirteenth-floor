/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <engine.h>


/* INCLUDES */
#include <graphics.h>
#include <SDL2/SDL.h>


namespace TF
{


/* METHOD DEFINITIONS */
Engine::Engine(Graphics* g)
{
	this->graphics = g;

	// TEMPORARY -------------------------------------------------------------------------------------
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.2f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.1f,  0.1f, 0.0f,
		 0.8f, -0.7f, 0.0f
	};

	std::vector<unsigned int> elements = {
		0, 3, 2,
		1, 3, 4
	};
	this->graphics->AddComponent(vertices, elements, "../shaders/test.vert", "../shaders/test.frag");
	// END TEMPORARY ---------------------------------------------------------------------------------
}

void Engine::mainLoop()
{
	bool running = true;
	while(running)
	{
		// Event polling
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) running = false;
		}

		this->graphics->Render();

		// Frame delay
		SDL_Delay(33);
	}
}


}
