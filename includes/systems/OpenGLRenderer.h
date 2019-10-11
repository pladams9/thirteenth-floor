
/*
 * graphics.h
 *
 *  Created on: Sep 13, 2019
 *      Author: pladams9
 */

#ifndef INCLUDES_GRAPHICS_H_
#define INCLUDES_GRAPHICS_H_


/* INCLUDES */
#include <engine/System.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <systems/OpenGL/ShaderManager.h>
#include <systems/OpenGL/ModelManager.h>


namespace TF
{


/* FORWARD DECLARATIONS */
namespace Comp
{
class Transform;
class Shader;
class ModelName;
}


namespace Sys
{


/* CLASS DECLARATION */
class OpenGLRenderer : public System
{
public:
	OpenGLRenderer(Engine* engine, int win_width, int win_height);

private:
	glm::mat4 view;
	glm::mat4 projection;

	OpenGL::ShaderManager shaders;
	OpenGL::ModelManager models;

	void Step();

	void UpdateView();

	void Render();

	void DrawEntity(Comp::ModelName* modelComp, Comp::Shader* shaderComp, Comp::Transform* transform);
};


}
}


#endif /* INCLUDES_GRAPHICS_H_ */
