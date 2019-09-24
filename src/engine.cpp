/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <engine.h>


/* INCLUDES */
#include <SDL2/SDL.h>

#include <systems/system.h>
#include <components/component.h>
#include <components/logicComp.h>

namespace TF
{


/* METHOD DEFINITIONS */
Engine::Engine()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

Engine::~Engine()
{
	SDL_Quit();
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

		for(std::pair<int, System*> system : this->systems)
			{
			system.second->Step();
			}
	}
}

EventManager* Engine::GetEventManager()
{
	return &this->eventManager;
}

void Engine::AddSystem(System* system, int priority)
{
	this->systems.insert(std::pair<int, System*>(priority, system));
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
	ComponentEntityMap* cm = &(this->components[comp->GetType()]);
	if(cm->find(entityID) == cm->end())
	{
		(*cm)[entityID] = comp;
	}
	else
	{
		// TODO: error handling
	}
}

std::vector<Entity> Engine::GetEntities(std::vector<ComponentType> required_comp_types, std::vector<ComponentType> optional_comp_types)
{
	// Get shortest component list
	ComponentType type_one;
	int min_size = -1;
	for(std::string type : required_comp_types)
	{
		if(((int)this->components[type].size() < min_size) || (min_size == -1))
		{
			type_one = type;
			min_size = this->components[type].size();
		}
	}

	// Get list of entities in that component list
	std::vector<EntityID> entityIDs;
	for(ComponentEntityMap::iterator it = this->components[type_one].begin(); it != this->components[type_one].end(); ++it)
	{
		entityIDs.push_back(it->first);
	}

	// Remove any entities not found in the other lists
	for(ComponentType type : required_comp_types)
	{
		if(type == type_one) continue;

		for(std::vector<EntityID>::iterator it = entityIDs.begin(); it != entityIDs.end();)
		{
			if(this->components[type].find(*it) == this->components[type].end())
			{
				entityIDs.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	// Build our return container
	std::vector<Entity> entities;
	for(EntityID e : entityIDs)
	{
	ComponentTypeMap ctm;
		for(ComponentType type : required_comp_types)
		{
			ctm.insert(std::pair<ComponentType, Component*>(type, this->components[type][e]));
		}
		for(ComponentType type : optional_comp_types)
		{
			if(this->components[type].find(e) != this->components[type].end())
			{
				ctm.insert(std::pair<ComponentType, Component*>(type, this->components[type][e]));
			}
		}
		entities.push_back(Entity(e, ctm));
	}

	return entities;
}


}
