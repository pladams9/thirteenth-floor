/*
 * Shader.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: pladams9
 */

#include <systems/OpenGL/ShaderManager.h>


/* INCLUDES */
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger.h"


namespace TF
{
namespace Sys
{
namespace OpenGL
{


/* METHOD DEFINITIONS */
void ShaderManager::LoadShader(std::string shader_name)
{
	std::string vertShaderPath = this->shaderPath + shader_name + ".vert";
	std::string fragShaderPath = this->shaderPath + shader_name + ".frag";

	// Load shaders from file
	std::fstream fs;
	std::stringstream buffer;

	fs.open(vertShaderPath, std::fstream::in);
	buffer << fs.rdbuf();
	std::string vertexShaderSource = buffer.str();
	const char* vss = vertexShaderSource.c_str();
	buffer.str("");
	fs.close();

	fs.open(fragShaderPath, std::fstream::in);
	buffer << fs.rdbuf();
	std::string fragmentShaderSource = buffer.str();
	const char* fss = fragmentShaderSource.c_str();
	fs.close();

	// Create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vss, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::stringstream error_msg;
		error_msg << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog;
		LOGGER().Log(ERROR, error_msg.str());
	}

	// Create fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fss, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::stringstream error_msg;
		error_msg << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog;
		LOGGER().Log(ERROR, error_msg.str());
	}

	// Link shaders to program
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	// Store shader
	this->shaders[shader_name] = programID;
}

void ShaderManager::Use(std::string shader_name)
{
	if(this->shaders.find(shader_name) == this->shaders.end())
	{
		this->LoadShader(shader_name);
	}
	glUseProgram(this->shaders.at(shader_name));
	this->currentShader = this->shaders.at(shader_name);
}

void ShaderManager::SetUniformMat4f(std::string name, glm::mat4 data)
{
	int location = glGetUniformLocation(this->currentShader, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(data));
}

void ShaderManager::SetUniformVec3f(std::string name, glm::vec3 data)
{
	int location = glGetUniformLocation(this->currentShader, name.c_str());
	glUniform3fv(location, 1, &data[0]);
}

void ShaderManager::SetUniformVec3f(std::string name, Util::vec3f data)
{
	int location = glGetUniformLocation(this->currentShader, name.c_str());
	glUniform3fv(location, 1, &data.vals[0]);
}

void ShaderManager::SetUniformVec3f(std::string name, Util::vec3d data)
{
	int location = glGetUniformLocation(this->currentShader, name.c_str());
	Util::vec3f data_f;
	data_f.x = (float)data.x;
	data_f.y = (float)data.y;
	data_f.z = (float)data.z;
	glUniform3fv(location, 1, &data_f.vals[0]);
}

void ShaderManager::SetUniformFloat(std::string name, float data)
{
	int location = glGetUniformLocation(this->currentShader, name.c_str());
	glUniform1f(location, data);
}


}
}
}
