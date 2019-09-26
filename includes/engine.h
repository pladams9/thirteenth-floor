/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_


/* INCLUDES */
#include <unordered_map>
#include <map>
#include <string>
#include <vector>

#include <entity.h>
#include <components/component.h>
#include <events.h>


namespace TF
{


/* FORWARD DECLARATIONS */
class System;


/* CLASS DECLARATIONS */
class Engine
{
private:
	EventManager eventManager;
	std::multimap<int, System*> systems;
	EntityID nextEntityID = 0;
	std::unordered_map<std::string, ComponentEntityMap> components;
	bool running = false;

public:
	Engine();
	~Engine();

	void Start();
	void Stop();
	void MainLoop();

	EventManager* GetEventManager();
	void AddSystem(System* system, int priority=0);
	void AddEntity(std::vector<Component*> comps);
	void AddComponent(Component* comp, EntityID entityID);

	std::vector<Entity> GetEntities(std::vector<ComponentType> required_comp_types, std::vector<ComponentType> optional_comp_types={});
};


}


#endif /* INCLUDES_ENGINE_H_ */
