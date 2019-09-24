/*
 * factory.cpp
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#include <builders.h>


/* INCLUDES */
#include <random>
#include <chrono>
#include <functional>

#include <components/component.h>
#include <components/rotater_logic.h>
#include <components/shaderComp.h>
#include <components/transformComps.h>
#include <components/vertexListComp.h>
#include <components/cameraTarget.h>


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
	comps.push_back(new TF::VertexListComp(vertices, elements, 36));
	comps.push_back(new TF::ShaderComp("../shaders/test.vert", "../shaders/test.frag"));
	comps.push_back(new TF::PositionComp(r_float(), r_float(), r_float()));
	TF::RotationComp* rc = new TF::RotationComp();
	comps.push_back(rc);
	comps.push_back(new TF::RotaterLogic(rc));
	comps.push_back(new TF::ScaleComp((r_float() + 1.0f) / 5.0f));

	return comps;
}

std::vector<Component*> Camera()
{
	std::vector<Component*> comps;

	comps.push_back(new TF::PositionComp(0, 3, -2));
	comps.push_back(new TF::CameraTargetPosComp(0, 0, 0));

	return comps;
}

}
}
