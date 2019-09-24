/*
 * cameraTarget.h
 *
 *  Created on: Sep 22, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_CAMERATARGET_H_
#define COMPONENTS_CAMERATARGET_H_


/* INCLUDES */
#include <components/component.h>

#include <string>
#include <array>


namespace TF
{


/* CLASS DEFINTIONS */
class CameraTargetPosComp : public Component
{
private:
	std::array<float, 3> position;

public:
	std::string GetType() const { return "CameraTargetPosComp"; }
	CameraTargetPosComp(float x=0.0, float y=0.0, float z=0.0) { this->SetPosition(x, y, z); }

	void SetPosition(float x, float y, float z) { this->position[0] = x; this->position[1] = y; this->position[2] = z; }
	std::array<float, 3> GetPosition() { return this->position; }
};


}


#endif /* COMPONENTS_CAMERATARGET_H_ */
