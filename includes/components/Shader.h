/*
 * shader.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_SHADER_H_
#define COMPONENTS_SHADER_H_


/* INCLUDES */
#include <engine/Component.h>
#include <string>


namespace TF
{
namespace Comp
{


class Shader : public Component
{
private:
	std::string name;

public:
	std::string GetType() const { return "Shader"; }
	Shader(std::string name) : name(name) {}

	std::string GetName() { return name; }
};


}
}


#endif /* COMPONENTS_SHADER_H_ */
