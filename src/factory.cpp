/*
 * factory.cpp
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#include <factory.h>


/* INCLUDES */
#include <component.h>
#include <vertexListComp.h>
#include <shaderComp.h>
#include <transformComps.h>
#include <rotater_logic.h>


namespace TF
{
namespace Factory
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

	std::vector<Component*> comps;
	comps.push_back(new TF::VertexListComp(vertices, elements, 36));
	comps.push_back(new TF::ShaderComp("../shaders/test.vert", "../shaders/test.frag"));
	comps.push_back(new TF::PositionComp(0.1, -0.2, 0.0));
	TF::RotationComp* rc = new TF::RotationComp();
	comps.push_back(rc);
	comps.push_back(new TF::RotaterLogic(rc));
	comps.push_back(new TF::ScaleComp());

	return comps;
}


}
}
