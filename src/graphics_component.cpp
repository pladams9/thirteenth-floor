/*
 * graphics_component.cpp
 *
 *  Created on: Sep 14, 2019
 *      Author: pladams9
 */

#include <graphics_component.h>


/* INCLUDES */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <GL/glew.h>


namespace TF
{


/* METHOD DEFINITIONS */
GraphicsComponent::GraphicsComponent()
{
	// Generate buffers
	glGenBuffers(1, &this->VBO_ID);
	glGenBuffers(1, &this->EBO_ID);
	glGenVertexArrays(1, &this->VAO_ID);

	// Setup VAO
	glBindVertexArray(this->VAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO, VBO, and EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GraphicsComponent::UpdateVertices(std::vector<float> vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicsComponent::UpdateElements(std::vector<unsigned int> elements, unsigned int count)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->EBO_count = count;
}

void GraphicsComponent::LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// Load shaders from file
	std::fstream fs;
	std::stringstream buffer;

	fs.open(vertexShaderPath, std::fstream::in);
	buffer << fs.rdbuf();
	std::string vertexShaderSource = buffer.str();
	const char* vss = vertexShaderSource.c_str();
	buffer.str("");
	fs.close();

	fs.open(fragmentShaderPath, std::fstream::in);
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

void GraphicsComponent::Draw()
{
	glUseProgram(this->shaderProgram);
	glBindVertexArray(this->VAO_ID);
	glDrawElements(GL_TRIANGLES, this->EBO_count, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


}
