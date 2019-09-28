/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <components/LogicComponent.h>
#include <Component.h>
#include <Engine.h>
#include <SDL2/SDL.h>

#include <System.h>

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

void Engine::Start()
{
	this->running = true;
	this->MainLoop();
}

void Engine::Stop()
{
	this->running = false;
}

void Engine::MainLoop()
{
	while(this->running)
	{
		for(Callback callback : frameStartCallbacks[FIRST])
		{
			//call callback
		}
		for(Callback callback : frameStartCallbacks[MIDDLE])
		{
			//call callback
		}
		for(auto it = frameStartCallbacks[LAST].rbegin(); it != frameStartCallbacks[LAST].rend();	++it)
		{
			//call callback
		}

		for(TimestepCallback callback : timestepCallbacks[FIRST])
		{
			//call callback
		}
		for(TimestepCallback callback : timestepCallbacks[MIDDLE])
		{
			//call callback
		}
		for(auto it = timestepCallbacks[LAST].rbegin(); it != timestepCallbacks[LAST].rend(); ++it)
		{
			//call callback
		}

		for(Callback callback : frameEndCallbacks[FIRST])
		{
			//call callback
		}
		for(Callback callback : frameEndCallbacks[MIDDLE])
		{
			//call callback
		}
		for(auto it = frameEndCallbacks[LAST].rbegin(); it != frameEndCallbacks[LAST].rend(); ++it)
		{
			//call callback
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

void Engine::RegisterFrameStartCallback(Callback fn, LoopSubStage lss)
{
	this->frameStartCallbacks[lss].push_back(fn);
}

void Engine::RegisterTimeStepCallback(Callback fn, LoopSubStage lss, Milliseconds ms)
{
	this->timestepCallbacks[lss].push_back(TimestepCallback(ms, fn));
}

void Engine::RegisterFrameEndCallback(Callback fn, LoopSubStage lss)
{
	this->frameEndCallbacks[lss].push_back(fn);
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
