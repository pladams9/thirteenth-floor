/*
 * rotater_logic.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef ROTATER_LOGIC_H_
#define ROTATER_LOGIC_H_


/* INCLUDES */
#include <logicComp.h>
#include <transformComps.h>

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

#endif /* ROTATER_LOGIC_H_ */
