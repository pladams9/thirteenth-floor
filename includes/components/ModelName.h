/*
 * ModelName.h
 *
 *  Created on: Oct 1, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_MODELNAME_H_
#define COMPONENTS_MODELNAME_H_


/* INCLUDES */
#include <engine/Component.h>
#include <string>


namespace TF
{
namespace Comp
{


class ModelName : public Component
{
private:
	std::string name;

public:
	std::string GetType() const { return "ModelName"; }
	ModelName(std::string name) : name(name) {}

	std::string GetName() { return name; }
};


}
}


#endif /* COMPONENTS_MODELNAME_H_ */
