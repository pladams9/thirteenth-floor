
/*
 * graphics.h
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_GRAPHICS_H_
#define INCLUDES_GRAPHICS_H_


/* INCLUDES */
#include <vector>

#include <glm/glm.hpp>

#include <System.h>


namespace TF
{


/* FORWARD DECLARATIONS */
namespace Comp
{
class VertexList;
class Shader;
class Position;
class Scale;
class Rotation;
}


namespace Sys
{


/* CLASS DECLARATION */
class Graphics : public System
{
private:
	glm::mat4 view;
	glm::mat4 projection;
public:
	Graphics(Engine* engine, int win_width, int win_height, std::string win_title);

	void Step();

	void Render();
	void UpdateCamera();
	void DrawEntity(Comp::VertexList* vertComp, Comp::Shader* shaderComp, Comp::Position* posComp, Comp::Scale* scaleComp, Comp::Rotation* rotComp);
};


}
}


#endif /* INCLUDES_GRAPHICS_H_ */
