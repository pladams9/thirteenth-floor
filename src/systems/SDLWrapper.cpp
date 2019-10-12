/*
 * SDLWrapper.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: pladams9
 */

#include <systems/SDLWrapper.h>


/* INCLUDES */
# include <Utilities.h>


namespace TF
{
namespace Sys
{


/* METHOD DEFINITIONS */
SDLWrapper::SDLWrapper(Engine* eng)
: System(eng)
{
	this->InitSDL();
	this->InitWindow();

	this->_engine->RegisterFrameStartCallback
	(
			[this]{ this->HandleSDLEvents(); },
			Engine::FIRST
	);
	this->_engine->RegisterFrameEndCallback
	(
			[this]{ this->SwapWindow(); },
			Engine::LAST
	);
}

SDLWrapper::~SDLWrapper()
{
	this->DestroyWindow();
	this->QuitSDL();
}

void SDLWrapper::InitSDL()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}


void SDLWrapper::QuitSDL()
{
	SDL_Quit();
}

void SDLWrapper::InitWindow()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	int win_width = dm.w;
	int win_height = dm.h + 1;

	// Set OpenGL attributes
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
			SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS
	);
	this->context = SDL_GL_CreateContext(this->window);
}

void SDLWrapper::DestroyWindow()
{
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
}

void SDLWrapper::SwapWindow()
{
	SDL_GL_SwapWindow(this->window);
}

void SDLWrapper::HandleSDLEvents()
{
	SDL_Event SDL_event;
	while(SDL_PollEvent(&SDL_event))
	{
		switch(SDL_event.type)
		{
		case SDL_QUIT :
			this->_engine->Stop();
			break;

		case SDL_KEYDOWN :
			if(SDL_event.key.repeat > 0) break; // Disregard key repeats
			this->_engine->GetEventManager()->TriggerEvent(Event(
					"KEY_DOWN",
					{
							{"keycode", Util::to_string(SDL_event.key.keysym.sym)}
					}
			));

			if(SDL_event.key.keysym.sym == SDLK_ESCAPE) this->_engine->Stop();
			break;

		case SDL_KEYUP :
			this->_engine->GetEventManager()->TriggerEvent(Event(
					"KEY_UP",
					{
							{"keycode", Util::to_string(SDL_event.key.keysym.sym)}
					}
			));
			break;

		case SDL_MOUSEBUTTONDOWN :
			this->_engine->GetEventManager()->TriggerEvent(Event(
					"MOUSE_DOWN",
					{
							{"x", Util::to_string(SDL_event.button.x)},
							{"y", Util::to_string(SDL_event.button.y)}
					}
			));
			break;

		case SDL_MOUSEBUTTONUP :
			this->_engine->GetEventManager()->TriggerEvent(Event(
					"MOUSE_UP",
					{
							{"x", Util::to_string(SDL_event.button.x)},
							{"y", Util::to_string(SDL_event.button.y)}
					}
			));
			break;
		}
	}
}


}
}




