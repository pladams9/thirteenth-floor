/*
 * factory.cpp
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#include <EntityBuilders.h>

#include <random>
#include <chrono>
#include <functional>
#include <iostream>

#include <Component.h>
#include <components/CameraTargetPosition.h>
#include <components/Controller.h>
#include <components/RotaterLogic.h>
#include <components/Shader.h>
#include <components/Transform.h>
#include <components/VertexList.h>


namespace TF
{
namespace Create
{

float r_float()
{
	// Random number generation
	static std::default_random_engine r_gen;
	static std::uniform_real_distribution<float> r_dist(-1.0, 1.0);
	static bool seeded = false;
	if(!seeded)
	{
		auto r_seed = std::chrono::system_clock::now().time_since_epoch().count();
		r_gen.seed(r_seed);
		seeded = true;
	}

	return r_dist(r_gen);
}


/* FUNCTION DEFINITIONS */
std::vector<Component*> Cube()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// Add components
	std::vector<Component*> comps;
	comps.push_back(new Comp::VertexList(vertices, 36));
	comps.push_back(new Comp::Shader("test"));
	float bounds = 20.0f;
	comps.push_back(new Comp::Position(r_float() * bounds, r_float() * bounds, r_float() * bounds));
	Comp::Rotation* rc = new Comp::Rotation();
	comps.push_back(rc);
	//comps.push_back(new Comp::RotaterLogic(rc));
	comps.push_back(new Comp::Scale(1.5f + (r_float())));

	return comps;
}

std::vector<Component*> Camera()
{
	std::vector<Component*> comps;

	comps.push_back(new Comp::Position(0, 0, 0));
	comps.push_back(new Comp::Direction(0, 0, -1));
	comps.push_back(new Comp::Controller());

	return comps;
}

}
}
