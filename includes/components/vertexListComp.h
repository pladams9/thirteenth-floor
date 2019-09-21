/*
 * vertexListComp.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_VERTEXLISTCOMP_H_
#define COMPONENTS_VERTEXLISTCOMP_H_


/* INCLUDES */
#include <components/component.h>
#include <vector>
#include <string>


namespace TF
{


class VertexListComp : public Component
{
private:
	unsigned int VBO_ID = 0;
	unsigned int EBO_ID = 0;
	unsigned int EBO_count = 0;
	unsigned int VAO_ID = 0;
	std::vector<float> vertices;
public:
	std::string GetType() const { return "VertexListComp"; }
	VertexListComp(std::vector<float> vertices, std::vector<int> elements, unsigned int count);

	unsigned int GetVAO();
	unsigned int GetElementCount();
};


}


#endif /* COMPONENTS_VERTEXLISTCOMP_H_ */
