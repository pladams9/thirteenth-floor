/*
 * LightSource.h
 *
 *  Created on: Oct 1, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_LIGHTSOURCE_H_
#define COMPONENTS_LIGHTSOURCE_H_


/* INCLUDES */
#include <string>

#include "engine/Component.h"
#include "Vec.h"


namespace TF
{
namespace Comp
{


enum LightType
{
	POINT,
	DIRECTIONAL
};


struct Light
{
	LightType lightType = POINT;

	Util::vec3d position = Util::vec3d(0.0, 0.0, 0.0);
	Util::vec3d direction = Util::vec3d(0.0, -1.0, 0.0);

	Util::vec3d ambient = Util::vec3d(0.0, 0.0, 0.0);
	Util::vec3d diffuse = Util::vec3d(0.0, 0.0, 0.0);
	Util::vec3d specular = Util::vec3d(.0, 0.0, 0.0);

	float constant = 1.0;
	float linear = 0.09;
	float quadratic = 0.032;

	bool castsShadows = false;
};


class LightSource : public Component
{
public:
	std::string GetType() const { return "LightSource"; }
	LightSource(Light light) : _light(light) {}

	Light GetLight() { return _light; }

private:
	Light _light;
};


}
}


#endif /* COMPONENTS_LIGHTSOURCE_H_ */
