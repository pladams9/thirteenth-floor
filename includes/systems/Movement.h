/*
 * Movement.h
 *
 *  Created on: Sep 26, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_MOVEMENT_H_
#define SYSTEMS_MOVEMENT_H_


#include <systems/system.h>


namespace TF
{


/* CLASS DECLARATION */
class MovementSystem : public System
{
public:
	MovementSystem(Engine* eng);

	void Step();
};


}


#endif /* SYSTEMS_MOVEMENT_H_ */
