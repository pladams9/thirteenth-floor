/*
 * factory.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef ENTITYBUILDERS_H_
#define ENTITYBUILDERS_H_


/* INCLUDES */
#include <vector>


namespace TF
{


/* FORWARD DECLARATIONS */
class Component;


/* FACTORY */
namespace Create
{

std::vector<Component*> Cube();
std::vector<Component*> Camera();

}


}


#endif /* ENTITYBUILDERS_H_ */
