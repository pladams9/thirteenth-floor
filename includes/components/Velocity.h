/*
 * Velocity.h
 *
 *  Created on: Oct 7, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_VELOCITY_H_
#define COMPONENTS_VELOCITY_H_


/* INCLUDES */
#include <engine/Component.h>
#include <string>
#include <cmath>

#include "Utilities.h"


namespace TF
{
namespace Comp
{


class Velocity : public Component
{
public:
	std::string GetType() const { return "Velocity"; }

	void SetVelocity(Util::vec3d new_velocity)
	{
		_velocity = new_velocity;
		CapVelocity();
	}
	void SetVelocity(double x_vel, double y_vel, double z_vel)
	{
		_velocity.x = x_vel;
		_velocity.y = y_vel;
		_velocity.z = z_vel;
		CapVelocity();
	}
	Util::vec3d GetVelocity()
	{
		return _velocity;
	}

	void SetMaxVelocity(double new_max_velocity) { _maxVelocity = new_max_velocity; }

	void Accelerate(Util::vec3d acceleration)
	{
		_velocity += acceleration;
		CapVelocity();
	}
	void Accelerate(double x_vel, double y_vel, double z_vel)
	{
		_velocity.x += x_vel;
		_velocity.y += y_vel;
		_velocity.z += z_vel;
		CapVelocity();
	}

private:
	Util::vec3d _velocity;
	double _maxVelocity;

	void CapVelocity()
	{
		if(_maxVelocity == 0) return;
		double magnitude = sqrt(
				(_velocity.x * _velocity.x) +
				(_velocity.y * _velocity.y) +
				(_velocity.z * _velocity.z)
		);
		if(magnitude > _maxVelocity)
		{
			_velocity /= magnitude;
			_velocity *= _maxVelocity;
		}
	}
};


}
}


#endif /* COMPONENTS_VELOCITY_H_ */
