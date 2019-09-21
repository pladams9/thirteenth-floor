/*
 * factory.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef FACTORY_H_
#define FACTORY_H_


/* INCLUDES */
#include <vector>


namespace TF
{


/* FORWARD DECLARATIONS */
class Component;


/* FACTORY */
namespace Factory
{

std::vector<Component*> Cube();

}


}


#endif /* FACTORY_H_ */
