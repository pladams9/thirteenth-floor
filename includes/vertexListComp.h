/*
 * vertexListComp.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef VERTEXLISTCOMP_H_
#define VERTEXLISTCOMP_H_


/* INCLUDES */
#include <component.h>

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


#endif /* VERTEXLISTCOMP_H_ */
