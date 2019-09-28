/*
 * shader.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_SHADER_H_
#define COMPONENTS_SHADER_H_


/* INCLUDES */
#include <Component.h>
#include <string>


namespace TF
{
namespace Comp
{


class Shader : public Component
{
private:
	unsigned int shaderProgram = 0;
	std::string vertShaderPath;
	std::string fragShaderPath;

public:
	std::string GetType() const { return "Shader"; }
	Shader(std::string vertShaderPath, std::string fragShaderPath);

	unsigned int GetProgram();
};


}
}


#endif /* COMPONENTS_SHADER_H_ */