/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <engine.h>


/* INCLUDES */
#include <SDL2/SDL.h>

#include <graphics.h>
#include <component.h>


namespace TF
{


/* METHOD DEFINITIONS */
Engine::Engine(Graphics* g)
{
	this->graphics = g;
	g->SetEngine(this);
}

void Engine::MainLoop()
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

void Engine::AddEntity(std::vector<Component*> comps)
{
	EntityID entityID = this->nextEntityID++;

	for (Component* comp : comps)
	{
		this->AddComponent(comp, entityID);
	}
}

void Engine::AddComponent(Component* comp, EntityID entityID)
{
	ComponentMap* cm = &(this->components[comp->GetType()]);
	if(cm->find(entityID) == cm->end())
	{
		(*cm)[entityID] = comp;
	}
	else
	{
		// TODO: error handling
	}
}

std::vector<std::vector<Component*>> Engine::GetComponents(std::vector<std::string> comp_types)
{
	// Get shortest component list
	std::string type_one;
	int min_size = -1;
	for(std::string type : comp_types)
	{
		if(((int)this->components[type].size() < min_size) || (min_size == -1))
		{
			type_one = type;
			min_size = this->components[type].size();
		}
	}

	// Get list of entities in that component list
	std::vector<EntityID> entities;
	for(ComponentMap::iterator it = this->components[type_one].begin(); it != this->components[type_one].end(); ++it)
	{
		entities.push_back(it->first);
	}

	// Remove any entities not found in the other lists
	for(std::string type : comp_types)
	{
		if(type == type_one) continue;

		for(std::vector<EntityID>::iterator it = entities.begin(); it != entities.end();)
		{
			if(this->components[type].find(*it) == this->components[type].end())
			{
				entities.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	// Build our return container
	std::vector<std::vector<Component*>> comps;
	for(EntityID e : entities)
	{
	std::vector<Component*> c;
		for(std::string type : comp_types)
		{
			c.push_back(this->components[type][e]);
		}
		comps.push_back(c);
	}

	return comps;
}


}
