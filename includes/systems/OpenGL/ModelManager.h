/**
 * ModelManager.h
 *
 */

#ifndef SYSTEMS_OPENGL_MODELMANAGER_H_
#define SYSTEMS_OPENGL_MODELMANAGER_H_


/* INCLUDES */
#include <string>
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


namespace TF
{
namespace Sys
{
namespace OpenGL
{


struct SingleModel
{
	unsigned int VAO = 0;
	unsigned int vertexCount = 0;
};

struct InstancedModel
{
	unsigned int VAO = 0;
	unsigned int vertexCount = 0;
	unsigned int instanceCount = 0;
};


class ModelManager
{
public:
	SingleModel GetSingleModel(std::string model_name);
	InstancedModel GetInstancedModel(std::string model_name);
	void UpdateInstances(std::vector<float> vertices);
private:
	std::unordered_map<std::string, unsigned int> _vertexVBOs;
	std::unordered_map<std::string, unsigned int> _vertexCounts;
	std::unordered_map<std::string, unsigned int> _instanceVBOs;
	std::unordered_map<std::string, SingleModel> _singleModels;
	std::unordered_map<std::string, InstancedModel> _instancedModels;

	void CreateSingleModel(std::string model_name);
	void CreateInstancedModel(std::string model_name);

	const std::string _modelPath = "../models/";
	void LoadVerticesFromFile(std::string model_name);
};


}
}
}


#endif /* SYSTEMS_OPENGL_MODELMANAGER_H_ */
