/*
 * component.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef ENGINE_COMPONENT_H_
#define ENGINE_COMPONENT_H_


/* INCLUDES */
#include <string>
#include <unordered_map>

namespace TF
{


/* CLASS DECLARATIONS */
class Component
{
public:
	virtual ~Component() = default;
	virtual std::string GetType() const =0;
};


/* TYPEDEFS */
using ComponentType = std::string;
using ComponentTypeMap = std::unordered_map<ComponentType, Component*>;


}


#endif /* ENGINE_COMPONENT_H_ */
