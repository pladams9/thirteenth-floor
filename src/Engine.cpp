/*
 * engine.cpp
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#include <Engine.h>


/* INCLUDES */
#include <System.h>
#include <Component.h>
#include <components/LogicComponent.h>
#include "Utilities.h"
#include "Logger.h"


namespace TF
{


/* METHOD DEFINITIONS */
Engine::~Engine()
{
	for(System* system : this->systems)
	{
		delete system;
	}
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
	this->lastStep = std::chrono::steady_clock::now();
	while(this->running)
	{
		// FRAME START CALLBACKS
		for(Callback callback : frameStartCallbacks[FIRST]) { callback(); }
		for(Callback callback : frameStartCallbacks[MIDDLE]) { callback(); }
		for(auto it = frameStartCallbacks[LAST].rbegin(); it != frameStartCallbacks[LAST].rend(); ++it) { (*it)(); }

		// TIMESTEP CALLBACKS
		std::chrono::steady_clock::time_point new_time = std::chrono::steady_clock::now();
		Milliseconds time_elapsed = std::chrono::duration_cast<Milliseconds>(new_time - this->lastStep);
		this->lastStep = new_time;
		LOGGER().Log(INFO, "Frame Length: " + Util::to_string(time_elapsed.count()) + "ms", true);

		for(TimestepCallback& ts_callback : timestepCallbacks[FIRST])
		{
			ts_callback.leftover += time_elapsed;
			while(ts_callback.leftover > ts_callback.timestep)
			{
				ts_callback.leftover -= ts_callback.timestep;
				ts_callback.callback();
			}
		}
		for(TimestepCallback& ts_callback : timestepCallbacks[MIDDLE])
		{
			ts_callback.leftover += time_elapsed;
			while(ts_callback.leftover > ts_callback.timestep)
			{
				ts_callback.leftover -= ts_callback.timestep;
				ts_callback.callback();
			}
		}
		for(auto it = timestepCallbacks[LAST].rbegin(); it != timestepCallbacks[LAST].rend(); ++it)
		{
			(*it).leftover += time_elapsed;
			while((*it).leftover > (*it).timestep)
			{
				(*it).leftover -= (*it).timestep;
				(*it).callback();
			}
		}

		// FRAME END CALLBACKS
		for(Callback callback : frameEndCallbacks[FIRST]) { callback(); }
		for(Callback callback : frameEndCallbacks[MIDDLE]) { callback(); }
		for(auto it = frameEndCallbacks[LAST].rbegin(); it != frameEndCallbacks[LAST].rend(); ++it) { (*it)(); }
	}
}

EventManager* Engine::GetEventManager()
{
	return &this->eventManager;
}

void Engine::AddSystem(System* system)
{
	this->systems.push_back(system);
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

void Engine::RegisterTimestepCallback(Callback fn, Milliseconds ms, LoopSubStage lss)
{
	TimestepCallback tsc;
	tsc.callback = fn;
	tsc.timestep = ms;
	tsc.leftover = Milliseconds(0.0);
	this->timestepCallbacks[lss].push_back(tsc);
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
			else
			{
				ctm.insert(std::pair<ComponentType, Component*>(type, nullptr));
			}
		}
		entities.push_back(Entity(e, ctm));
	}

	return entities;
}


}
