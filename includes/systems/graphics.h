/*
 * graphics.h
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_GRAPHICS_H_
#define INCLUDES_GRAPHICS_H_


/* INCLUDES */
#include <SDL2/SDL.h>

#include <vector>


namespace TF {


/* FORWARD DECLARATIONS */
class Engine;
class VertexListComp;
class ShaderComp;
class PositionComp;
class RotationComp;

class Graphics
{
private:
	SDL_Window* window;
	SDL_GLContext context;
	Engine* engine = nullptr;
public:
	Graphics();
	~Graphics();

	void SetEngine(Engine* eng) {this->engine = eng;};

	void Render();
	void DrawEntity(VertexListComp* vertComp, ShaderComp* shaderComp, PositionComp* posComp, RotationComp* rotComp);
};


}


#endif /* INCLUDES_GRAPHICS_H_ */