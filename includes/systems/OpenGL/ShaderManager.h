/*
 * Shader.h
 *
 *  Created on: Oct 1, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_OPENGL_SHADER_H_
#define SYSTEMS_OPENGL_SHADER_H_


/* INCLUDES */
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace TF
{
namespace Sys
{
namespace OpenGL
{


class ShaderManager
{
public:
	void Use(std::string shader_name);

	void SetUniformMat4f(std::string name, glm::mat4 data);
private:
	const std::string shaderPath = "../shaders/";

	std::unordered_map<std::string, unsigned int> shaders;
	unsigned int currentShader = 0;

	void LoadShader(std::string shader_name);
};


}
}
}


#endif /* SYSTEMS_OPENGL_SHADER_H_ */
