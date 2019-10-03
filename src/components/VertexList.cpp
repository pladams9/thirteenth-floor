/*
 * vertexListComp.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: pladams9
 */

#include <components/VertexList.h>
#include <GL/glew.h>


namespace TF
{
namespace Comp
{


VertexList::VertexList(std::vector<float> vertices, unsigned int count)
{
	// Generate buffers
	glGenBuffers(1, &this->VBO_ID);
	glGenVertexArrays(1, &this->VAO_ID);

	// Setup VAO
	glBindVertexArray(this->VAO_ID);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_ID);
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Update vertices
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	this->count = count;

	// Unbind VAO, VBO, and EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int VertexList::GetVAO()
{
	return this->VAO_ID;
}

unsigned int VertexList::GetCount()
{
	return this->count;
}


}
}
