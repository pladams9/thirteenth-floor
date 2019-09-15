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
class GraphicsComponent;


class Graphics
{
private:
	SDL_Window* window;
	SDL_GLContext context;

	std::vector<GraphicsComponent*> gfxComps;
public:
	Graphics();
	~Graphics();

	void AddComponent(std::vector<float> vertices, std::vector<unsigned int> elements, const char* vertexShader, const char* fragmentShader);
	void Render();
};


}


#endif /* INCLUDES_GRAPHICS_H_ */
