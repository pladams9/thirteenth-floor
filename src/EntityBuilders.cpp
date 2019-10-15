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
#include "components/Voxels.h"
#include "components/VoxelDrawable.h"
#include <engine/Component.h>
#include "Drawable.h"


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
	std::vector<Component*> comps;

	Util::Drawable d;
	d.modelName = "cube";
	d.shaderName = "test";
	comps.push_back(new Comp::MeshDrawable(d));

	Comp::Transform* t = new Comp::Transform;
	t->SetPosition(0.0, 0.0, 0.0);
	comps.push_back(t);

	return comps;
}

std::vector<Component*> RandomCube()
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



std::vector<Component*> VoxelChunk(std::function<void(Comp::Voxels*)> generator)
{
	std::vector<Component*> comps;

	Util::Drawable d;
	d.modelName = "cube";
	d.shaderName = "test";
	Util::Material m;
	m.diffuse = Util::vec3f(0.1, 0.6, 0.1);
	m.ambient = Util::vec3f(0.1, 0.6, 0.1);
	d.material = m;

	Util::Drawable d2;
	d2.modelName = "cube";
	d2.shaderName = "test";
	m.diffuse = Util::vec3f(0.5, 0.3, 0.0);
	m.ambient = Util::vec3f(0.5, 0.3, 0.0);
	d2.material = m;

	// VoxelDrawable
	Comp::VoxelDrawable* vd = new Comp::VoxelDrawable(
			{
				std::pair<VoxelType, Util::Drawable>(0, d),
				std::pair<VoxelType, Util::Drawable>(1, d2)
			},
			0.15
	);
	comps.push_back(vd);

	// Transform
	Comp::Transform* t = new Comp::Transform;
	t->SetPosition(0.0, -5.0, 0.0);
	comps.push_back(t);

	// Voxels
	Comp::Voxels* v = new Comp::Voxels;
	if(generator) generator(v);
	comps.push_back(v);

	return comps;
}

std::vector<Component*> Camera()
{
	std::vector<Component*> comps;

	comps.push_back(new Comp::Transform(Util::vec3d(-10, 5, 5), Util::vec3d(1), Util::vec3d(-0.4, -0.4, 0)));
	comps.push_back(new Comp::Camera());
	//comps.push_back(new Comp::CameraTargetPosition());
	comps.push_back(new Comp::Controller());

	return comps;
}


}


namespace VoxGen
{


void Ring(Comp::Voxels* voxels)
{
	int x_size = 150;
	int y_size = 50;
	int z_size = 150;
	double radius = 50.0;

	int hx_size = x_size / 2;
	int hy_size = y_size / 2;
	int hz_size = z_size / 2;
	for(int x = -hx_size; x < hx_size; ++x)
	{
		for(int y = -hy_size; y < hy_size; ++y)
		{
			for(int z = -hz_size; z < hz_size; ++z)
			{
				double c_dist = abs(radius - sqrt((double)((x*x) + (z*z))));
				double dist = sqrt((c_dist*c_dist) + (y*y));

				double density = 1.0 / (1.0 + dist);
				if(density > 0.2)
					{
					if(y > 1) voxels->AddVoxel(0, Util::vec3d(x, y, z));
					else voxels->AddVoxel(1, Util::vec3d(x, y, z));
					}
			}
		}
	}
}

void Block(Comp::Voxels* voxels)
{
	int x_size = 4;
	int y_size = 4;
	int z_size = 4;

	int hx_size = x_size / 2;
	int hy_size = y_size / 2;
	int hz_size = z_size / 2;

	for(int x = -hx_size; x < hx_size; ++x)
	{
		for(int y = -hy_size; y < hy_size; ++y)
		{
			for(int z = -hz_size; z < hz_size; ++z)
			{
				voxels->AddVoxel(0, Util::vec3d(x, y, z));
			}
		}
	}
}


}
}
