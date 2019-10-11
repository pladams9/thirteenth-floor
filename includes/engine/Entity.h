/*
 * entity.h
 *
 *  Created on: Sep 25, 2019
 *      Author: pladams9
 */

#ifndef ENGINE_ENTITY_H_
#define ENGINE_ENTITY_H_


/* INCLUDES */
#include <engine/Component.h>


namespace TF
{


/* TYPEDEFS */
using EntityID = unsigned int;
using ComponentEntityMap = std::unordered_map<EntityID, Component*>;


/* CONSTANTS */
const EntityID NULL_ENTITY = 0;

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
	EntityID _entityID = NULL_ENTITY;
	ComponentTypeMap _components;

};


}


#endif /* ENGINE_ENTITY_H_ */
