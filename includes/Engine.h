/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_


/* INCLUDES */
#include <functional>
#include <chrono>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>

#include <Component.h>
#include <Entity.h>
#include <Events.h>


namespace TF
{


/* FORWARD DECLARATIONS */
class System;


/* CLASS DECLARATIONS */
class Engine
{
	using Milliseconds = std::chrono::duration<double, std::milli>;
	using Callback = std::function<void(Milliseconds)>;
	using TimestepCallback = std::pair<Milliseconds, Callback>;

public:
	Engine();
	~Engine();

	EventManager* GetEventManager();
	void AddSystem(System* system, int priority=0);
	void AddEntity(std::vector<Component*> comps);
	void AddComponent(Component* comp, EntityID entityID);

	enum LoopSubStage {FIRST, MIDDLE, LAST};
	void RegisterFrameStartCallback(Callback fn, LoopSubStage lss);
	void RegisterTimeStepCallback(Callback fn, LoopSubStage lss, Milliseconds ms);
	void RegisterFrameEndCallback(Callback fn, LoopSubStage lss);

	void Start();
	void Stop();
	void MainLoop();

	std::vector<Entity> GetEntities(std::vector<ComponentType> required_comp_types, std::vector<ComponentType> optional_comp_types={});

private:
	EventManager eventManager;

	std::multimap<int, System*> systems;
	EntityID nextEntityID = 0;
	std::unordered_map<std::string, ComponentEntityMap> components;

	bool running = false;

	std::array<std::vector<Callback>, 3> frameStartCallbacks;
	std::array<std::vector<Callback>, 3> frameEndCallbacks;
	std::array<std::vector<TimestepCallback>, 3> timestepCallbacks;
};


}


#endif /* INCLUDES_ENGINE_H_ */
