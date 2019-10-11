/*
 * logicComp.h
 *
 *  Created on: Sep 21, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_LOGICCOMPONENT_H_
#define COMPONENTS_LOGICCOMPONENT_H_


/* INCLUDES */
#include <engine/Component.h>
#include <string>


namespace TF
{
namespace Comp
{


class LogicComponent : public Component
{
public:
	std::string GetType() const { return "LogicComponent"; }

	virtual void Step()=0;
};


}
}


#endif /* COMPONENTS_LOGICCOMPONENT_H_ */
