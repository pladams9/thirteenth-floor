/*
 * Camera.h
 *
 *  Created on: Oct 8, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_CAMERA_H_
#define COMPONENTS_CAMERA_H_


/* INCLUDES */
#include <string>

#include "engine/Component.h"


namespace TF
{
namespace Comp
{


class Camera : public Component
{
public:
	std::string GetType() const { return "Camera"; }
	Camera(bool active = true) : _active(active) {}

	void SetActive(bool active) { _active = active; }
	bool IsActive() const { return _active; }

private:
	bool _active;
};


}
}


#endif /* COMPONENTS_CAMERA_H_ */
