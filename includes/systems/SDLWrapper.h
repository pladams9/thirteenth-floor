/*
 * SDLWrapper.h
 *
 *  Created on: Sep 30, 2019
 *      Author: pladams9
 */

#ifndef SDL_SDLWRAPPER_H_
#define SDL_SDLWRAPPER_H_


#include <engine/System.h>
#include <SDL2/SDL.h>


namespace TF
{
namespace Sys
{


/* CLASS DECLARATION */
class SDLWrapper : public System
{
public:
	SDLWrapper(Engine* eng);
	~SDLWrapper();

private:
	void InitSDL();
	void QuitSDL();

	void InitWindow();
	void DestroyWindow();
	void SwapWindow();

	void HandleSDLEvents();

	SDL_Window* window;
	SDL_GLContext context;
};


}
}


#endif /* SDL_SDLWRAPPER_H_ */
