/*
 * engine.h
 *
 *  Created on: Sep 10, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_ENGINE_H_
#define INCLUDES_ENGINE_H_


/* INCLUDES */
#include <engine/Component.h>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>

#include <engine/Entity.h>
#include <engine/Events.h>


namespace TF
{


/* FORWARD DECLARATIONS */
class System;


/* CLASS DECLARATIONS */
using Milliseconds = std::chrono::duration<double, std::milli>;
using Callback = std::function<void()>;
struct TimestepCallback
{
	Callback callback;
	Milliseconds timestep;
	Milliseconds leftover;
};

class Engine
{
public:
	~Engine();

	EventManager* GetEventManager();
	void AddSystem(System* system);
	void AddEntity(std::vector<Component*> comps);
	void AddComponent(Component* comp, EntityID entityID);

	enum LoopSubStage {FIRST, MIDDLE, LAST};
	void RegisterFrameStartCallback(Callback fn, LoopSubStage lss = MIDDLE);
	void RegisterTimestepCallback(Callback fn, Milliseconds ms, LoopSubStage lss = MIDDLE);
	void RegisterFrameEndCallback(Callback fn, LoopSubStage lss = MIDDLE);

	void Start();
	void Stop();
	void MainLoop();

	std::vector<Entity> GetEntities(std::vector<ComponentType> required_comp_types, std::vector<ComponentType> optional_comp_types={});

private:
	EventManager eventManager;

	std::vector<System*> systems;
	EntityID nextEntityID = 1;
	std::unordered_map<std::string, ComponentEntityMap> components;

	bool running = false;
	std::chrono::steady_clock::time_point lastStep;

	std::array<std::vector<Callback>, 3> frameStartCallbacks;
	std::array<std::vector<Callback>, 3> frameEndCallbacks;
	std::array<std::vector<TimestepCallback>, 3> timestepCallbacks;
};


}


#endif /* INCLUDES_ENGINE_H_ */
