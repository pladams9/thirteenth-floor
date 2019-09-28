/*
 * vertexListComp.h
 *
 *  Created on: Sep 15, 2019
 *      Author: pladams9
 */

#ifndef COMPONENTS_VERTEXLIST_H_
#define COMPONENTS_VERTEXLIST_H_


/* INCLUDES */
#include <Component.h>
#include <vector>
#include <string>


namespace TF
{
namespace Comp
{


class VertexList : public Component
{
private:
	unsigned int VBO_ID = 0;
	unsigned int EBO_ID = 0;
	unsigned int EBO_count = 0;
	unsigned int VAO_ID = 0;
	std::vector<float> vertices;
public:
	std::string GetType() const { return "VertexList"; }
	VertexList(std::vector<float> vertices, std::vector<int> elements, unsigned int count);

	unsigned int GetVAO();
	unsigned int GetElementCount();
};


}
}


#endif /* COMPONENTS_VERTEXLIST_H_ */
