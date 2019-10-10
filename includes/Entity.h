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
using ComponentEntityMap = std::unordered_map<EntityID, Component*>;

/* CLASS DEFINITION */
class Entity
{
public:
	Entity(EntityID entityID, ComponentTypeMap components) : _entityID(entityID), _components(components) {}
	Entity() = default;

	Component* operator[](ComponentType ct)
	{
		if(_components.find(ct) !=_components.end())
			return _components.at(ct);
		else
			return nullptr;
	}

	EntityID GetID() { return _entityID; }

private:
	EntityID _entityID = 0;
	ComponentTypeMap _components;

};


}


#endif /* ENTITY_H_ */
