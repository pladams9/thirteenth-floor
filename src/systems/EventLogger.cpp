/*
 * EventLogger.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#include <engine/Events.h>
#include <systems/EventLogger.h>

/* INCLUDES */
#include <sstream>

#include "Logger.h"

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
		std::stringstream log_msg;
		if(e.GetEventType() == "KEY_DOWN") log_msg << "KEY_DOWN, Keycode: " << e.GetStringData("keycode");
		if(e.GetEventType() == "KEY_UP") log_msg << "KEY_UP, Keycode: " << e.GetStringData("keycode");
		if(e.GetEventType() == "MOUSE_DOWN") log_msg << "MOUSE_DOWN, x, y: " << e.GetStringData("x") << ", " << e.GetStringData("y");
		if(e.GetEventType() == "MOUSE_UP") log_msg << "MOUSE_UP, x, y: " << e.GetStringData("x") << ", " << e.GetStringData("y");
		LOGGER().Log(INFO, log_msg.str());
	}
}


}
}
