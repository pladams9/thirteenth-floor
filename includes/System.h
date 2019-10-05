/*
 * system.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


/* INCLUDES */
#include <engine/Events.h>
#include <Engine.h>

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
};


}


#endif /* SYSTEM_H_ */
