/*
 * vertexListComp.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: pladams9
 */

#include <components/vertexListComp.h>
#include <GL/glew.h>


namespace TF
{


VertexListComp::VertexListComp(std::vector<float> vertices, std::vector<int> elements, unsigned int count)
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

	// Update vertices
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// Update elements
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);
	this->EBO_count = count;

	// Unbind VAO, VBO, and EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int VertexListComp::GetVAO()
{
	return this->VAO_ID;
}

unsigned int VertexListComp::GetElementCount()
{
	return this->EBO_count;
}


}
