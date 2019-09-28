/*
 * Control.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#include <components/Controller.h>


namespace TF
{
namespace Comp
{


Controller::Controller()
{
	this->flags["MOVE_LEFT"] = false;
	this->flags["MOVE_RIGHT"] = false;
	this->flags["MOVE_FORWARD"] = false;
	this->flags["MOVE_BACKWARD"] = false;
	this->flags["TURN_LEFT"] = false;
	this->flags["TURN_RIGHT"] = false;
	this->flags["LOOK_UP"] = false;
	this->flags["LOOK_DOWN"] = false;
}

void Controller::SetFlag(std::string key, bool val)
{
	this->flags[key] = val;
}

bool Controller::GetFlag(std::string key)
{
	if(this->flags.find(key) != this->flags.end())
	{
		return this->flags.at(key);
	}
	else return false;
}


}
}
