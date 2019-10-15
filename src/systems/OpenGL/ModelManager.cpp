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
#include "Utilities.h"


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
	_vertices[model_name] = vertices;

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

	_singleModels[model_name] = model;

	TF::LOGGER().Log(DEBUG, "Finished ModelManager::CreateSingleModel(\"" + model_name + "\")");
}

void ModelManager::CreateInstancedModel(std::string model_name, unsigned int sub_id)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::CreateInstancedModel(\"" + model_name + "\", " + Util::to_string(sub_id) + ")");

	InstancedModel model;

	if(_vertexVBOs.find(model_name) == _vertexVBOs.end())
	{
		TF::LOGGER().Log(DEBUG, "Model not found");
		// Load Vertices VBO
		LoadVerticesFromFile(model_name);
	}
	model.vertexCount = _vertexCounts[model_name];

	// Create Instances VBO
	glGenBuffers(1, &_instanceVBOs[model_name + Util::to_string(sub_id)]);
	model.instanceCount = 0;

	// Create VAO
	glGenVertexArrays(1, &model.VAO);
	glBindVertexArray(model.VAO);

	// Vertex Attributes
	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBOs[model_name + Util::to_string(sub_id)]);
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind VAO and VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_instancedModels[model_name + Util::to_string(sub_id)] = model;

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

InstancedModel ModelManager::GetInstancedModel(std::string model_name, unsigned int sub_id)
{
	InstancedModel model;
	if(_instancedModels.find(model_name + Util::to_string(sub_id)) == _instancedModels.end())
	{
		CreateInstancedModel(model_name, sub_id);
	}
	model = _instancedModels.at(model_name + Util::to_string(sub_id));
	return model;
}

void ModelManager::UpdateInstances(std::string model_name, unsigned int sub_id, std::vector<float> vertices, float scale)
{
	TF::LOGGER().Log(DEBUG, "Starting ModelManager::UpdateInstances(\"" + model_name + "\")");

	// Update positions in instance VBO
	if(_instanceVBOs.find(model_name + Util::to_string(sub_id)) == _instanceVBOs.end())
	{
		CreateInstancedModel(model_name, sub_id);
	}

	std::vector<float> verts;
	for(unsigned int i = 0; i < (vertices.size() / 3); ++i)
	{
		for(unsigned int j = 0; j < (_vertices[model_name].size() / 6); ++j)
		{
			verts.push_back((vertices[3 * i] + _vertices[model_name][6 * j]) * scale);
			verts.push_back((vertices[(3 * i) + 1] + _vertices[model_name][(6 * j) + 1]) * scale);
			verts.push_back((vertices[(3 * i) + 2] + _vertices[model_name][(6 * j) + 2]) * scale);
			verts.push_back(_vertices[model_name][(6 * j) + 3]);
			verts.push_back(_vertices[model_name][(6 * j) + 4]);
			verts.push_back(_vertices[model_name][(6 * j) + 5]);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, _instanceVBOs[model_name + Util::to_string(sub_id)]);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), &verts[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Get instance count
	_instancedModels[model_name + Util::to_string(sub_id)].instanceCount = vertices.size();

	TF::LOGGER().Log(DEBUG, "Finished ModelManager::UpdateInstances(\"" + model_name + "\")");
}


}
}
}
