/*
 * KeyboardController.cpp
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#include <systems/KeyboardController.h>

/* INCLUDES */
#include <iostream>
#include <components/Control.h>
#include <Events.h>


namespace TF
{


/* STATIC MEMBER INITIALIZATION */
std::unordered_map<std::string, EventType> KeyboardControllerSystem::eventMap = {
		{"1073741904", "TURN_LEFT"},	// Left
		{"1073741903", "TURN_RIGHT"},	// Right
		{"1073741905", "LOOK_UP"},		// Down
		{"1073741906", "LOOK_DOWN"},	// Up
		{"97", "MOVE_LEFT"},			// A
		{"100", "MOVE_RIGHT"},			// D
		{"119", "MOVE_FORWARD"},		// W
		{"115", "MOVE_BACKWARD"}		// S
};

/* METHOD DEFINITIONS */
KeyboardControllerSystem::KeyboardControllerSystem(Engine* eng) : System(eng)
{
	this->eventQueue.Listen("KEY_DOWN");
	this->eventQueue.Listen("KEY_UP");
}

void KeyboardControllerSystem::Step()
{
	std::vector<Entity> entities = this->engine->GetEntities({"ControlComp"});

	Event e;
	while(this->eventQueue.PollEvents(e))
	{
		std::string keycode = e.GetStringData("keycode");
		std::string flag;
		if(this->eventMap.find(keycode) != this->eventMap.end()) flag = this->eventMap.at(keycode);
		else continue;

		bool val;
		if(e.GetEventType() == "KEY_DOWN") val = true;
		else val = false;

		for(Entity entity : entities)
		{
			{
				dynamic_cast<ControlComp*>(entity.second.at("ControlComp"))->SetFlag(flag, val);
			}
		}
	}
}


}
