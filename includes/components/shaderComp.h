/*
 * shader.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_SHADERCOMP_H_
#define COMPONENTS_SHADERCOMP_H_


/* INCLUDES */
#include <components/component.h>
#include <string>



namespace TF
{


class ShaderComp : public Component
{
private:
	unsigned int shaderProgram = 0;
	std::string vertShaderPath;
	std::string fragShaderPath;

public:
	std::string GetType() const { return "ShaderComp"; }
	ShaderComp(std::string vertShaderPath, std::string fragShaderPath);

	unsigned int GetProgram();
};


}


#endif /* COMPONENTS_SHADERCOMP_H_ */
