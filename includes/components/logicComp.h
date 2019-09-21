/*
 * logicComp.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_LOGICCOMP_H_
#define COMPONENTS_LOGICCOMP_H_


/* INCLUDES */
#include <components/component.h>
#include <string>



namespace TF
{


class LogicComp : public Component
{
public:
	std::string GetType() const { return "LogicComp"; }

	virtual void Step()=0;
};


}


#endif /* COMPONENTS_LOGICCOMP_H_ */
