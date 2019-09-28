/*
 * Control.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

/* INCLUDES */
#include <Component.h>
#include <unordered_map>
#include <string>


namespace TF
{


class ControlComp : public Component
{
private:
	std::unordered_map<std::string, bool> flags;

public:
	std::string GetType() const { return "ControlComp"; }
	ControlComp();

	void SetFlag(std::string key, bool val);
	bool GetFlag(std::string key);
};


}
