/*
 * SDLEvents.h
 *
 *  Created on: Sep 24, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_SDLEVENTHANDLER_H_
#define SYSTEMS_SDLEVENTHANDLER_H_

#include <System.h>


namespace TF
{
namespace Sys
{


/* CLASS DECLARATION */
class SDLEventHandler : public System
{
public:
	SDLEventHandler(Engine* eng);

	void Step();
};


}
}


#endif /* SYSTEMS_SDLEVENTHANDLER_H_ */
