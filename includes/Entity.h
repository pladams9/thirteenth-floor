/*
 * entity.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef ENTITY_H_
#define ENTITY_H_


/* INCLUDES */
#include <Component.h>


namespace TF
{


/* TYPEDEFS */
using EntityID = unsigned int;
using Entity = std::pair<EntityID, ComponentTypeMap>;
using ComponentEntityMap = std::unordered_map<EntityID, Component*>;


}


#endif /* ENTITY_H_ */
