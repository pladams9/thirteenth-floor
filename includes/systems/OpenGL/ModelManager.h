/*
 * Model.h
 *
 *  Created on: Oct 1, 2019
 *      Author: pladams9
 */

#ifndef SYSTEMS_OPENGL_MODELMANAGER_H_
#define SYSTEMS_OPENGL_MODELMANAGER_H_


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


struct Model
{
	unsigned int VBO = 0;
	unsigned int VAO = 0;
	unsigned int count = 0;
};


class ModelManager
{
public:
	Model GetModel(std::string model_name);
private:
	const std::string modelPath = "../models/";

	std::unordered_map<std::string, Model> models;

	void LoadModel(std::string model_name);
};


}
}
}


#endif /* SYSTEMS_OPENGL_MODELMANAGER_H_ */
