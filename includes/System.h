/*
 * system.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


/* INCLUDES */
#include <Engine.h>
#include <Events.h>

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


#endif /* SYSTEM_H_ */
