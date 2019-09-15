/*
 * graphics_component.h
 *
 *  Created on: Sep 14, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_GRAPHICS_COMPONENT_H_
#define INCLUDES_GRAPHICS_COMPONENT_H_


/* INCLUDES */
#include <vector>


namespace TF
{


class GraphicsComponent
{
private:
	unsigned int VBO_ID = 0;
	unsigned int EBO_ID = 0;
	unsigned int EBO_count = 0;
	unsigned int VAO_ID = 0;
	unsigned int shaderProgram = 0;
public:
	GraphicsComponent();
	void UpdateVertices(std::vector<float> vertices);
	void UpdateElements(std::vector<unsigned int> elements, unsigned int count);
	void LoadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void Draw();
};


}


#endif /* INCLUDES_GRAPHICS_COMPONENT_H_ */
