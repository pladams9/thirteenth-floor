/*
 * logic.cpp
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#include <components/LogicComponent.h>
#include <Component.h>
#include <systems/Logic.h>
#include <vector>
#include <string>


using namespace std::chrono;

namespace TF
{
namespace Sys
{


LogicSystem::LogicSystem(Engine* engine) : System(engine)
{
	this->engine->RegisterTimestepCallback
	(
			[this]() { this->Step(); },
			Milliseconds(30.0)
	);

	this->lastStep = steady_clock::now();
	this->timeStep = duration<double, std::milli>(30.0);
	this->leftoverTime = duration<double>(0);
}

void LogicSystem::Step()
{
	steady_clock::time_point new_time = steady_clock::now();
	duration<double, std::milli> time_elapsed = duration_cast<duration<double>>(new_time - this->lastStep);
	time_elapsed += this->leftoverTime;

	while(time_elapsed > this->timeStep)
	{
		for(Entity entity : this->engine->GetEntities({"LogicComponent"}))
		{
			dynamic_cast<Comp::LogicComponent*>(entity.second.at("LogicComponent"))->Step();
		}
	time_elapsed -= this->timeStep;
	}

	this->leftoverTime = time_elapsed;
	this->lastStep = new_time;
}


}
}
