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
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
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
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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


}
}
}
