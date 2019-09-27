/*
 * KeyboardController.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_KEYBOARDCONTROLLER_H_
#define SYSTEMS_KEYBOARDCONTROLLER_H_


#include <systems/system.h>


namespace TF
{


/* CLASS DECLARATION */
class KeyboardControllerSystem : public System
{
public:
	KeyboardControllerSystem(Engine* eng);

	void Step();

private:
	static std::unordered_map<std::string, EventType> eventMap;
};


}


#endif /* SYSTEMS_KEYBOARDCONTROLLER_H_ */
