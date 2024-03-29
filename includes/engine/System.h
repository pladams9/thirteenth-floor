/*
 * system.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef ENGINE_SYSTEM_H_
#define ENGINE_SYSTEM_H_


/* INCLUDES */
#include <engine/Engine.h>
#include <engine/Events.h>

namespace TF
{


/* CLASS DEFINITION */
class System
{
protected:
	Engine* _engine;
	EventQueue _eventQueue;

public:
	System(Engine* eng) : _engine(eng), _eventQueue(eng->GetEventManager()) {}
};


}


#endif /* ENGINE_SYSTEM_H_ */
