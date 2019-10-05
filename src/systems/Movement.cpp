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
	std::vector<Entity> entities = this->engine->GetEntities({"Controller", "Position", "Direction"});

	for(Entity entity : entities)
	{
		// TODO: make component speed
		float speed = 0.003;
		float rot_speed = 0.0001;

		Comp::Controller* control = dynamic_cast<Comp::Controller*>(entity.second.at("Controller"));
		Comp::Position* position = dynamic_cast<Comp::Position*>(entity.second.at("Position"));
		Comp::Direction* direction = dynamic_cast<Comp::Direction*>(entity.second.at("Direction"));

		std::array<float, 3> pos = position->GetPosition();
		glm::vec3 g_pos = glm::vec3(pos[0], pos[1], pos[2]);
		std::array<float, 3> dir = direction->GetDirection();
		glm::vec3 g_dir = glm::vec3(dir[0], dir[1], dir[2]);

		// Position
		if(control->GetFlag("MOVE_LEFT")) g_pos -= glm::normalize(glm::cross(g_dir, glm::vec3(0,1,0))) * speed;
		if(control->GetFlag("MOVE_RIGHT")) g_pos += glm::normalize(glm::cross(g_dir, glm::vec3(0,1,0))) * speed;
		if(control->GetFlag("MOVE_FORWARD")) g_pos += g_dir * speed;
		if(control->GetFlag("MOVE_BACKWARD")) g_pos -= g_dir * speed;

		position->SetPosition(g_pos.x, g_pos.y, g_pos.z);

		// Direction
		float pitch = atan2(g_dir.y, (sqrt((g_dir.x*g_dir.x)+(g_dir.z*g_dir.z))));
		float yaw = atan2(g_dir.z, g_dir.x);

		if(control->GetFlag("LOOK_UP")) pitch += rot_speed;
		if(control->GetFlag("LOOK_DOWN")) pitch -= rot_speed;
		if(control->GetFlag("TURN_LEFT")) yaw -= rot_speed;
		if(control->GetFlag("TURN_RIGHT")) yaw += rot_speed;

		if(pitch > 1.5) pitch = 1.5;
		if(pitch < -1.5) pitch = -1.5;

		g_dir.x = cos(pitch) * cos(yaw);
		g_dir.y = sin(pitch);
		g_dir.z = cos(pitch) * sin(yaw);
		g_dir = glm::normalize(g_dir);
		direction->SetDirection(g_dir.x, g_dir.y, g_dir.z);
	}
}


}
}
