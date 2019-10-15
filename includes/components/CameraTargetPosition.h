/*
 * cameraTarget.h
 *
 *  Created on: Sep 22, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_CAMERATARGETPOSITION_H_
#define COMPONENTS_CAMERATARGETPOSITION_H_


/* INCLUDES */
#include <engine/Component.h>
#include <string>

#include "Vec.h"


namespace TF
{
namespace Comp
{


/* CLASS DEFINTIONS */
class CameraTargetPosition : public Component
{
public:
	std::string GetType() const { return "CameraTargetPosition"; }
	CameraTargetPosition(Util::vec3d position = Util::vec3d(0.0, 0.0, 0.0)) : _position(position) {}
	CameraTargetPosition(double x, double y, double z) : _position(Util::vec3d(0.0, 0.0, 0.0)) {}

	void SetPosition(Util::vec3d new_position) { _position = new_position; }
	void SetPosition(double x, double y, double z) { _position = Util::vec3d(x, y, z); }

	Util::vec3d GetPosition() { return _position; }

private:
	Util::vec3d _position;
};


}
}


#endif /* COMPONENTS_CAMERATARGETPOSITION_H_ */
