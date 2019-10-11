/*
 * Physics.h
 *
 *  Created on: Oct 8, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_PHYSICS_H_
#define SYSTEMS_PHYSICS_H_


#include <engine/System.h>


namespace TF
{
namespace Sys
{


/* CLASS DECLARATION */
class Physics : public System
{
public:
	Physics(Engine* eng);

	void Step();
};


}
}


#endif /* SYSTEMS_PHYSICS_H_ */
