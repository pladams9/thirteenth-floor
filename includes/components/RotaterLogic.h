/*
 * rotater_logic.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_ROTATERLOGIC_H_
#define COMPONENTS_ROTATERLOGIC_H_


/* INCLUDES */
#include <components/LogicComponent.h>
#include <components/Transform.h>

namespace TF
{


class RotaterLogic : public LogicComp
{
private:
	RotationComp* rotComp;
	float r = 0.0;
public:
	RotaterLogic(RotationComp* r) { this->rotComp = r; }
	void Step()
	{
		r += 0.05f;
		this->rotComp->SetRotation(r, 0.5, 1, 0);
	}
};


}

#endif /* COMPONENTS_ROTATERLOGIC_H_ */
