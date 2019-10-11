/*
 * Control.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_CONTROLLER_H_
#define COMPONENTS_CONTROLLER_H_

/* INCLUDES */
#include <engine/Component.h>
#include <unordered_map>
#include <string>


namespace TF
{
namespace Comp
{


class Controller : public Component
{
private:
	std::unordered_map<std::string, bool> flags;

public:
	std::string GetType() const { return "Controller"; }
	Controller();

	void SetFlag(std::string key, bool val);
	bool GetFlag(std::string key);
};


}
}

#endif /* COMPONENTS_CONTROLLER_H_ */
