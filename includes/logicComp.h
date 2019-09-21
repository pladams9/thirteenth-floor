/*
 * logicComp.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef LOGICCOMP_H_
#define LOGICCOMP_H_


/* INCLUDES */
#include <string>

#include <component.h>


namespace TF
{


class LogicComp : public Component
{
public:
	std::string GetType() const { return "LogicComp"; }

	virtual void Step()=0;
};


}


#endif /* LOGICCOMP_H_ */
