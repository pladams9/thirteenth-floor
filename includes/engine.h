/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_

#include <SDL2/SDL.h>
#include <GL/glew.h>

class Engine
{
private:
	static SDL_Window* window;
	static SDL_GLContext context;
public:
	static void Init();
	static void Render();
	static void Cleanup();
};


#endif /* INCLUDES_ENGINE_H_ */
