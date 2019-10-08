/*
 * ModelManager.cpp
 *
 *  Created on: Oct 5, 2019
 *      Author: pladams9
 */

#include <systems/OpenGL/ModelManager.h>


/* INCLUDES */
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

#include <GL/glew.h>

#include "Logger.h"


namespace TF
{
namespace Sys
{
namespace OpenGL
{


/* METHOD DEFINITIONS */
void ModelManager::LoadModel(std::string model_name)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::LoadModel()");
	std::string model_path = this->modelPath + model_name + ".TFmodel";

	// Load shaders from file
	std::ifstream fs;
	fs.open(model_path, std::fstream::in);

	unsigned int count;
	std::vector<float> vertices;

	std::string line;
	std::getline(fs, line);
	count = stoi(line);
	while(std::getline(fs, line, ','))
	{
		vertices.push_back(stof(line));
	}
	fs.close();


	Model model;

	// Generate buffers
	glGenBuffers(1, &model.VBO);
	glGenVertexArrays(1, &model.VAO);

	// Setup VAO
	glBindVertexArray(model.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, model.VBO);
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Update vertices
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	model.count = count;

	// Unbind VAO, VBO, and EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	this->models[model_name] = model;
}

Model ModelManager::GetModel(std::string model_name)
{
	Model model;
	if(this->models.find(model_name) == this->models.end())
	{
		this->LoadModel(model_name);
	}
	model = this->models.at(model_name);
	return model;
}


}
}
}
