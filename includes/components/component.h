/*
 * component.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_COMPONENT_H_
#define COMPONENTS_COMPONENT_H_


/* INCLUDES */
#include <string>

namespace TF
{


class Component
{
public:
	virtual ~Component() = default;
	virtual std::string GetType() const = 0;
};


}


#endif /* COMPONENTS_COMPONENT_H_ */
