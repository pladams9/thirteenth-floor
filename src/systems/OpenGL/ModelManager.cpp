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
void ModelManager::LoadVerticesFromFile(std::string model_name)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::LoadVerticesFromFile(\"" + model_name + "\")");

	// Open model file
	std::string model_path = _modelPath + model_name + ".TFmodel";
	std::ifstream fs;
	fs.open(model_path, std::fstream::in);
	std::string line;

	// Get vertex count
	std::getline(fs, line);
	_vertexCounts[model_name] = stoi(line);

	// Get vertices
	std::vector<float> vertices;
	while(std::getline(fs, line, ','))
	{
		vertices.push_back(stof(line));
	}
	fs.close();

	// Put vertices in VBO
	glGenBuffers(1, &_vertexVBOs[model_name]);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBOs[model_name]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	TF::LOGGER().Log(DEBUG, "Finished ModelManager::LoadVerticesFromFile(\"" + model_name + "\")");
}

void ModelManager::CreateSingleModel(std::string model_name)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::CreateSingleModel(\"" + model_name + "\")");

	SingleModel model;

	if(_vertexVBOs.find(model_name) == _vertexVBOs.end())
	{
		// Load Vertices VBO
		LoadVerticesFromFile(model_name);
	}
	model.vertexCount = _vertexCounts[model_name];

	// Create VAO
	glGenVertexArrays(1, &model.VAO);
	glBindVertexArray(model.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBOs[model_name]);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Unbind VAO, VBO, and EBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	_singleModels[model_name] = model;

	TF::LOGGER().Log(DEBUG, "Finished ModelManager::CreateSingleModel(\"" + model_name + "\")");
}

void ModelManager::CreateInstancedModel(std::string model_name)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::CreateInstancedModel(\"" + model_name + "\")");

	InstancedModel model;

	if(_vertexVBOs.find(model_name) == _vertexVBOs.end())
	{
		// Load Vertices VBO
		LoadVerticesFromFile(model_name);
	}
	model.vertexCount = _vertexCounts[model_name];

	// Create Instances VBO
	glGenBuffers(1, &_instanceVBOs[model_name]);
	model.instanceCount = 0;

	// Create VAO
	glGenVertexArrays(1, &model.VAO);
	glBindVertexArray(model.VAO);

	// Vertex Attributes
	glBindBuffer(GL_ARRAY_BUFFER, _vertexVBOs[model_name]);
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Instance Positions
	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBOs[model_name]);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(2, 1);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	_instancedModels[model_name] = model;

	TF::LOGGER().Log(DEBUG, "Finished ModelManager::CreateInstancedModel(\"" + model_name + "\")");
}

SingleModel ModelManager::GetSingleModel(std::string model_name)
{
	SingleModel model;
	if(_singleModels.find(model_name) == _singleModels.end())
	{
		CreateSingleModel(model_name);
	}
	model = _singleModels.at(model_name);
	return model;
}

InstancedModel ModelManager::GetInstancedModel(std::string model_name)
{
	InstancedModel model;
	if(_instancedModels.find(model_name) == _instancedModels.end())
	{
		CreateSingleModel(model_name);
	}
	model = _instancedModels.at(model_name);
	return model;
}


}
}
}
