/*
 * system.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_SYSTEM_H_
#define SYSTEMS_SYSTEM_H_


/* INCLUDES */
#include <engine.h>
#include <events.h>

namespace TF
{


/* CLASS DEFINITION */
class System
{
protected:
	Engine* engine;
	EventQueue eventQueue;

public:
	System(Engine* eng) : engine(eng), eventQueue(eng->GetEventManager()) {}
	virtual ~System() =default;
	virtual void Step() =0;
};


}


#endif /* SYSTEMS_SYSTEM_H_ */
