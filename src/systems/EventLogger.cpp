/*
 * EventLogger.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#include <Events.h>
#include <systems/EventLogger.h>

/* INCLUDES */
#include <iostream>


namespace TF
{
namespace Sys
{


/* METHOD DEFINITIONS */
EventLogger::EventLogger(Engine* eng) : System(eng)
{
	this->engine->RegisterFrameStartCallback
	(
			[this]() { this->Step(); }
	);

	this->eventQueue.Listen("KEY_DOWN");
	this->eventQueue.Listen("KEY_UP");
	this->eventQueue.Listen("MOUSE_DOWN");
	this->eventQueue.Listen("MOUSE_UP");
}

void EventLogger::Step()
{
	Event e;
	while(this->eventQueue.PollEvents(e))
	{
		if(e.GetEventType() == "KEY_DOWN") std::cout << "KEY_DOWN, Keycode: " << e.GetStringData("keycode") << std::endl;
		if(e.GetEventType() == "KEY_UP") std::cout << "KEY_UP, Keycode: " << e.GetStringData("keycode") << std::endl;
		if(e.GetEventType() == "MOUSE_DOWN")
			std::cout << "MOUSE_DOWN, x, y: " << e.GetStringData("x") << ", " << e.GetStringData("y") << std::endl;
		if(e.GetEventType() == "MOUSE_UP")
			std::cout << "MOUSE_UP, x, y: " << e.GetStringData("x") << ", " << e.GetStringData("y") << std::endl;
	}
}


}
}
