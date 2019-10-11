/*
 * KeyboardController.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_KEYBOARDINPUT_H_
#define SYSTEMS_KEYBOARDINPUT_H_


#include <engine/System.h>


namespace TF
{
namespace Sys
{


/* CLASS DECLARATION */
class KeyboardInput : public System
{
public:
	KeyboardInput(Engine* eng);

	void Step();

private:
	static std::unordered_map<std::string, EventType> eventMap;
};


}
}


#endif /* SYSTEMS_KEYBOARDINPUT_H_ */
