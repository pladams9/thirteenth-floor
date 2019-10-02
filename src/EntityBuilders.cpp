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
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f
	};
	std::vector<int> elements = {
		0, 1, 2,
		0, 1, 4,
		0, 2, 4,

		3, 1, 2,
		6, 2, 4,
		5, 1, 4,

		7, 3, 6,
		7, 5, 6,
		7, 3, 5,

		2, 3, 6,
		4, 5, 6,
		1, 3, 5
	};

	// Add components
	std::vector<Component*> comps;
	comps.push_back(new Comp::VertexList(vertices, elements, 36));
	comps.push_back(new Comp::Shader("test"));
	float bounds = 50.0f;
	comps.push_back(new Comp::Position(r_float() * bounds, r_float() * bounds, r_float() * bounds));
	Comp::Rotation* rc = new Comp::Rotation();
	comps.push_back(rc);
	comps.push_back(new Comp::RotaterLogic(rc));
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
