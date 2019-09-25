/*
 * EventLogger.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#include <systems/EventLogger.h>

/* INCLUDES */
#include <iostream>

#include <events.h>

namespace TF
{


/* METHOD DEFINITIONS */
EventLoggerSystem::EventLoggerSystem(Engine* eng) : System(eng)
{
	this->eventQueue.Listen("KEY_DOWN");
}

void EventLoggerSystem::Step()
{
	Event e;
	while(this->eventQueue.PollEvents(e))
	{
		if(e.GetEventType() == "KEY_DOWN") std::cout << "Keycode: " << e.GetStringData("keycode") << std::endl;
	}
}



}
