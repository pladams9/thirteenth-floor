/*
 * transform.h
 *
 *  Created on: Sep 20, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_TRANSFORMCOMPS_H_
#define COMPONENTS_TRANSFORMCOMPS_H_


/* INCLUDES */
#include <components/component.h>
#include <string>
#include <array>
#include <math.h>



namespace TF
{


/* CLASS DEFINTIONS */
class PositionComp : public Component
{
private:
	std::array<float, 3> position;

public:
	std::string GetType() const { return "PositionComp"; }
	PositionComp(float x=0.0, float y=0.0, float z=0.0) { this->SetPosition(x, y, z); }

	void SetPosition(float x, float y, float z) { this->position[0] = x; this->position[1] = y; this->position[2] = z; }
	std::array<float, 3> GetPosition() { return this->position; }
};


class RotationComp : public Component
{
private:
	float rotation;
	std::array<float, 3> axis;

public:
	std::string GetType() const { return "RotationComp"; }
	RotationComp(float r=0, float x=1.0, float y=0.0, float z=0.0) { this->SetRotation(r, x, y, z); }

	void SetRotation(float r, float x, float y, float z)
	{
		r = fmod(r, 360.0f);

		float total = fabs(x) + fabs(y) + fabs(z);
		x /= total;
		y /= total;
		z /= total;

		this->rotation = r;
		this->axis[0] = x;
		this->axis[1] = y;
		this->axis[2] = z;
	}
	float GetRotation() { return this->rotation; }
	std::array<float, 3> GetRotationAxis() { return this->axis; }
};


class ScaleComp : public Component
{
private:
	std::array<float, 3> scale;

public:
	std::string GetType() const { return "ScaleComp"; }
	ScaleComp(float scale=1.0) { this->SetScale(scale); }
	ScaleComp(float x, float y, float z) { this->SetScale(x, y, z); }

	void SetScale(float x, float y, float z) { this->scale[0] = x; this->scale[1] = y; this->scale[2] = z; }
	void SetScale(float scale) { this->scale[0] = scale; this->scale[1] = scale; this->scale[2] = scale; }
	std::array<float, 3> GetScale() { return this->scale; }
};


}


#endif /* COMPONENTS_TRANSFORMCOMPS_H_ */
