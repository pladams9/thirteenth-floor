/*
 * Movement.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: pladams9
 */

#include <systems/Movement.h>

/* INCLUDES */
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <components/Control.h>
#include <components/Transform.h>
#include <Events.h>


namespace TF
{


/* METHOD DEFINITIONS */
MovementSystem::MovementSystem(Engine* eng) : System(eng)
{}

void MovementSystem::Step()
{
	std::vector<Entity> entities = this->engine->GetEntities({"ControlComp", "PositionComp", "DirectionComp"});

	for(Entity entity : entities)
	{
		// TODO: make component speed
		float speed = 0.01;
		float rot_speed = 0.005;

		ControlComp* control = dynamic_cast<ControlComp*>(entity.second.at("ControlComp"));
		PositionComp* position = dynamic_cast<PositionComp*>(entity.second.at("PositionComp"));
		DirectionComp* direction = dynamic_cast<DirectionComp*>(entity.second.at("DirectionComp"));

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

