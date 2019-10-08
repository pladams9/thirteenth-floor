/*
 * Movement.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: pladams9
 */

#include <components/Controller.h>
#include <systems/Movement.h>

/* INCLUDES */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <components/Transform.h>
#include <engine/Events.h>


namespace TF
{
namespace Sys
{


/* METHOD DEFINITIONS */
MovementSystem::MovementSystem(Engine* eng) : System(eng)
{
	this->engine->RegisterTimestepCallback
	(
			[this]() { this->Step(); },
			Milliseconds(30)
	);
}

void MovementSystem::Step()
{
	std::vector<Entity> entities = this->engine->GetEntities({"Controller", "Transform"});

	for(Entity entity : entities)
	{
		// TODO: make component speed
		float speed = 0.8;
		float rot_speed = 0.04;

		Comp::Controller* control = dynamic_cast<Comp::Controller*>(entity.second.at("Controller"));
		Comp::Transform* transform = dynamic_cast<Comp::Transform*>(entity.second.at("Transform"));

		Util::vec3d pos = transform->GetPosition();
		glm::vec3 g_pos = glm::vec3(pos.x, pos.y, pos.z);
		Util::vec3d rot = transform->GetRotation();

		// Rotation
		if(control->GetFlag("LOOK_UP")) rot.pitch += rot_speed;
		if(control->GetFlag("LOOK_DOWN")) rot.pitch -= rot_speed;
		if(control->GetFlag("TURN_LEFT")) rot.yaw -= rot_speed;
		if(control->GetFlag("TURN_RIGHT")) rot.yaw += rot_speed;

		if(rot.pitch > 1.5) rot.pitch = 1.5;
		if(rot.pitch < -1.5) rot.pitch = -1.5;

		transform->SetRotation(rot.yaw, rot.pitch, rot.roll);

		// Get direction vector
		glm::vec3 g_dir;
		g_dir.x = cos(rot.pitch) * cos(rot.yaw);
		g_dir.y = sin(rot.pitch);
		g_dir.z = cos(rot.pitch) * sin(rot.yaw);
		g_dir = glm::normalize(g_dir);

		// Position
		if(control->GetFlag("MOVE_LEFT")) g_pos -= glm::normalize(glm::cross(g_dir, glm::vec3(0,1,0))) * speed;
		if(control->GetFlag("MOVE_RIGHT")) g_pos += glm::normalize(glm::cross(g_dir, glm::vec3(0,1,0))) * speed;
		if(control->GetFlag("MOVE_FORWARD")) g_pos += g_dir * speed;
		if(control->GetFlag("MOVE_BACKWARD")) g_pos -= g_dir * speed;

		transform->SetPosition(g_pos.x, g_pos.y, g_pos.z);
	}
}


}
}
