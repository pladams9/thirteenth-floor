/*
 * SDLEvent.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#include <systems/SDLEvents.h>

/* INCLUDES */
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>

#include <events.h>
#include <utilities.h>


namespace TF
{


/* METHOD DEFINITIONS */
SDLEventSystem::SDLEventSystem(Engine* eng) : System(eng) {}

void SDLEventSystem::Step()
{
	SDL_Event SDL_event;
	while(SDL_PollEvent(&SDL_event))
	{
		switch(SDL_event.type)
		{
		case SDL_QUIT :
			this->engine->Stop();
			break;

		case SDL_KEYDOWN :
			this->engine->GetEventManager()->TriggerEvent(Event(
					"KEY_DOWN",
					{
							{"keycode", Util::to_string(SDL_event.key.keysym.sym)}
					}
			));

			if(SDL_event.key.keysym.sym == SDLK_ESCAPE) this->engine->Stop();
			break;

		case SDL_KEYUP :
			this->engine->GetEventManager()->TriggerEvent(Event(
					"KEY_UP",
					{
							{"keycode", Util::to_string(SDL_event.key.keysym.sym)}
					}
			));
			break;

		case SDL_MOUSEBUTTONDOWN :
			this->engine->GetEventManager()->TriggerEvent(Event(
					"MOUSE_DOWN",
					{
							{"x", Util::to_string(SDL_event.button.x)},
							{"y", Util::to_string(SDL_event.button.y)}
					}
			));
			break;

		case SDL_MOUSEBUTTONUP :
			this->engine->GetEventManager()->TriggerEvent(Event(
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
