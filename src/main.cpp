#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

#include <engine.h>

int main( int argc, char* args[] )
{
	Engine::Init();

	// Logic setup
	float r, g, b;
	r = 0.1;
	g = 0.1;
	b = 0.8;

	bool running = true;
	while(running)
	{
		// Event polling
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT) running = false;
		}


		// Logic
		r += 0.1;
		g += 0.05;
		b += 0.8;
		if (r > 1.0) r -= 1.0;
		if (g > 1.0) g -= 1.0;
		if (b > 1.0) b -= 1.0;
		glClearColor(r, g, b, 1.0);

		Engine::Render();

		// Frame delay
		SDL_Delay(33);
	}

	Engine::Cleanup();

	return 0;
}
