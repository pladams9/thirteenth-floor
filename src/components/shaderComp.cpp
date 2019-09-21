/*
 * shaderComp.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: pladams9
 */

#include <components/shaderComp.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>


namespace TF
{


ShaderComp::ShaderComp(std::string vertShaderPath, std::string fragShaderPath)
{
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
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
}

unsigned int ShaderComp::GetProgram()
{
	return this->shaderProgram;
}


}
