/*
 * transform.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_TRANSFORM_H_
#define COMPONENTS_TRANSFORM_H_


/* INCLUDES */
#include <string>
#include <array>
#include <math.h>

#include "Component.h"
#include "Utilities.h"


namespace TF
{
namespace Comp
{


/* CLASS DEFINTIONS */
class Transform : public Component
{
public:
	std::string GetType() const { return "Transform"; }
	Transform(
			Util::vec3d position = Util::vec3d(0,0,0),
			Util::vec3d scale = Util::vec3d(1,1,1),
			Util::vec3d rotation = Util::vec3d(0,0,0)
			)
	: _position(position), _rotation(rotation), _scale(scale) {}
	Transform(
			Util::vec3d position,
			double scale,
			Util::vec3d rotation = Util::vec3d(0,0,0)
			)
	: _position(position), _rotation(rotation), _scale(Util::vec3d(scale)) {}

	Util::vec3d GetPosition() { return _position; }
	Util::vec3d GetRotation() { return _rotation; }
	Util::vec3d GetScale() { return _scale; }

	void SetPosition(Util::vec3d position) { _position = position; }
	void SetPosition(double x, double y, double z) { _position = Util::vec3d(x, y, z); }

	void SetRotation(Util::vec3d rotation) { _rotation = rotation; }
	void SetRotation(double yaw, double pitch, double roll) { _rotation = Util::vec3d(yaw, pitch, roll); }

	void SetScale(Util::vec3d scale) { _scale = scale; }
	void SetScale(double x, double y, double z) { _scale = Util::vec3d(x,y,z); }
	void SetScale(double scale) { _scale = Util::vec3d(scale); }

	void Translate(Util::vec3d translate_vector) { _position += translate_vector; }
	void Translate(double x, double y, double z)
	{
		_position.x += x;
		_position.y += y;
		_position.z += z;
	}

	void Rotate(Util::vec3d rotation_vector) { _rotation += rotation_vector; }
	void Rotate(double yaw, double pitch, double roll)
	{
		_rotation.yaw += yaw;
		_rotation.pitch += pitch;
		_rotation.roll += roll;
	}

private:
	Util::vec3d _position;
	Util::vec3d _rotation;
	Util::vec3d _scale;
};


class Direction : public Component
{
private:
	std::array<float, 3> direction;

public:
	std::string GetType() const { return "Direction"; }
	Direction(float x=0.0, float y=0.0, float z=0.0) { this->SetDirection(x, y, z); }

	void SetDirection(float x, float y, float z) { this->direction[0] = x; this->direction[1] = y; this->direction[2] = z; }
	std::array<float, 3> GetDirection() { return this->direction; }
};


}
}


#endif /* COMPONENTS_TRANSFORM_H_ */
