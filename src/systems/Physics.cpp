/*
 * Physics.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: pladams9
 */

#include <systems/Physics.h>

/* INCLUDES */
#include "components/Transform.h"
#include "components/Velocity.h"
#include "engine/Events.h"

namespace TF
{
namespace Sys
{

/* METHOD DEFINITIONS */
Physics::Physics(Engine* eng)
: System(eng)
{
	this->engine->RegisterTimestepCallback(
			[this]() { this->Step(); },
			Milliseconds(30.0)
	);
}
void Physics::Step()
{
	// TODO: Update acceleration

	// Apply acceleration
	std::vector<Entity> entities = this->engine->GetEntities({"Transform", "Velocity"});

	for(Entity entity : entities)
	{
		Comp::Transform* transform = static_cast<Comp::Transform*>(entity.second.at("Transform"));
		Comp::Velocity* velocity = static_cast<Comp::Velocity*>(entity.second.at("Velocity"));
		transform->Translate(velocity->GetVelocity());
	}
}


}
}
