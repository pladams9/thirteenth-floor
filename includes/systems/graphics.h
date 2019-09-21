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

#include <systems/system.h>


namespace TF {


/* FORWARD DECLARATIONS */
class VertexListComp;
class ShaderComp;
class PositionComp;
class RotationComp;

class Graphics : public System
{
private:
	SDL_Window* window;
	SDL_GLContext context;
public:
	Graphics(Engine* engine);
	~Graphics();

	void Step();

	void Render();
	void DrawEntity(VertexListComp* vertComp, ShaderComp* shaderComp, PositionComp* posComp, RotationComp* rotComp);
};


}


#endif /* INCLUDES_GRAPHICS_H_ */
