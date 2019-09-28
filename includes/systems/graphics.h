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

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <System.h>


namespace TF {


/* FORWARD DECLARATIONS */
class VertexListComp;
class ShaderComp;
class PositionComp;
class ScaleComp;
class RotationComp;


/* CLASS DECLARATION */
class Graphics : public System
{
private:
	SDL_Window* window;
	SDL_GLContext context;

	glm::mat4 view;
	glm::mat4 projection;
public:
	Graphics(Engine* engine, int win_width, int win_height, std::string win_title);
	~Graphics();

	void Step();

	void Render();
	void UpdateCamera();
	void DrawEntity(VertexListComp* vertComp, ShaderComp* shaderComp, PositionComp* posComp, ScaleComp* scaleComp, RotationComp* rotComp);
};


}


#endif /* INCLUDES_GRAPHICS_H_ */
