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

#include <components/CameraTargetPosition.h>
#include <components/Controller.h>
#include "components/Camera.h"
#include <components/Transform.h>
#include <components/Velocity.h>
#include "components/MeshDrawable.h"
#include <engine/Component.h>


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
	// Add components
	std::vector<Component*> comps;
	Util::Drawable d;
	d.modelName = "cube";
	d.shaderName = "test";
	comps.push_back(new Comp::MeshDrawable(d));
	float bounds = 20.0f;
	Comp::Transform* t = new Comp::Transform;
	t->SetPosition(
			r_float() * bounds,
			r_float() * bounds,
			r_float() * bounds
			);
	comps.push_back(t);
	Comp::Velocity* v = new Comp::Velocity;
	v->SetMaxVelocity(0.01);
	v->SetVelocity(r_float(),r_float(),r_float());
	comps.push_back(v);

	return comps;
}

std::vector<Component*> Camera()
{
	std::vector<Component*> comps;

	comps.push_back(new Comp::Transform(Util::vec3d(-10, 5, 25), Util::vec3d(3.14, 0, 0)));
	comps.push_back(new Comp::Camera());
	//comps.push_back(new Comp::CameraTargetPosition());
	comps.push_back(new Comp::Controller());

	return comps;
}

}
}
