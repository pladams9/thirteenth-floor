/*
 * SDLEvents.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_SDLEVENTS_H_
#define SYSTEMS_SDLEVENTS_H_

#include <systems/system.h>


namespace TF
{


/* CLASS DECLARATION */
class SDLEventSystem : public System
{
public:
	SDLEventSystem(Engine* eng);

	void Step();
};


}


#endif /* SYSTEMS_SDLEVENTS_H_ */
