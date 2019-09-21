/*
 * logic.cpp
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#include <systems/logic.h>


/* INCLUDES */
#include <vector>
#include <string>

#include <components/component.h>
#include <components/logicComp.h>

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
		for(std::vector<Component*> entity : this->engine->GetComponents({"LogicComp"}))
		{
			dynamic_cast<LogicComp*>(entity[0])->Step();
		}
	time_elapsed -= this->timeStep;
	}

	this->leftoverTime = time_elapsed;
	this->lastStep = new_time;
}


}