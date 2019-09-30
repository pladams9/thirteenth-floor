/*
 * factory.cpp
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#include <components/CameraTargetPosition.h>
#include <components/Controller.h>
#include <random>
#include <chrono>
#include <functional>

#include <components/RotaterLogic.h>
#include <components/Shader.h>
#include <components/Transform.h>
#include <components/VertexList.h>
#include <Component.h>
#include <EntityBuilders.h>


namespace TF
{
namespace Create
{


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

	// Random number generation
	std::default_random_engine r_gen;
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	r_gen.seed(seed);

	std::uniform_real_distribution<float> r_dist(-1,1);

	auto r_float = std::bind(r_dist, r_gen);

	// Add components
	std::vector<Component*> comps;
	comps.push_back(new Comp::VertexList(vertices, elements, 36));
	comps.push_back(new Comp::Shader("../shaders/test.vert", "../shaders/test.frag"));
	comps.push_back(new Comp::Position(r_float() * 10, r_float() * 10, r_float() * 10));
	Comp::Rotation* rc = new Comp::Rotation();
	comps.push_back(rc);
	comps.push_back(new Comp::RotaterLogic(rc));
	comps.push_back(new Comp::Scale((r_float() + 1.0f) / 2.0f));

	return comps;
}

std::vector<Component*> Camera()
{
	std::vector<Component*> comps;

	comps.push_back(new Comp::Position(0, 0, 3));
	comps.push_back(new Comp::Direction(0, 0, -1));
	comps.push_back(new Comp::Controller());

	return comps;
}

}
}
