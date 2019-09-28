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


LogicSystem::LogicSystem(Engine* engine) : System(engine)
{
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
		for(Entity entity : this->engine->GetEntities({"LogicComp"}))
		{
			dynamic_cast<LogicComp*>(entity.second.at("LogicComp"))->Step();
		}
	time_elapsed -= this->timeStep;
	}

	this->leftoverTime = time_elapsed;
	this->lastStep = new_time;
}


}
