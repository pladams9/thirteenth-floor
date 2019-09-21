/*
 * factory.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef BUILDERS_H_
#define BUILDERS_H_


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

}


}


#endif /* BUILDERS_H_ */
