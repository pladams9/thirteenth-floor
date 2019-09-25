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
		}
	}
}


}
