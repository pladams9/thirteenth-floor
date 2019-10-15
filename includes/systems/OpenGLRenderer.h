/**
 * OpenGLRenderer.h
 *
 * System for rendering graphics using OpenGL. Requires that an OpenGL context has been created.
 *
 */

#ifndef INCLUDES_GRAPHICS_H_
#define INCLUDES_GRAPHICS_H_


/* INCLUDES */
#include <vector>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "engine/System.h"
#include "systems/OpenGL/ShaderManager.h"
#include "systems/OpenGL/ModelManager.h"


namespace TF
{


/* FORWARD DECLARATIONS */
namespace Comp
{
class MeshDrawable;
class Transform;
class VoxelDrawable;
class Voxels;
}


namespace Sys
{


/* CLASS DECLARATION */
class OpenGLRenderer : public System
{
public:
	OpenGLRenderer(Engine* engine, int win_width, int win_height);

private:
	glm::mat4 _view;
	glm::vec3 _viewPos;
	glm::mat4 _projection;

	OpenGL::ShaderManager _shaders;
	OpenGL::ModelManager _models;

	void Step();

	void UpdateView();

	void Render();

	void DrawMesh(Comp::MeshDrawable* meshDrawable, Comp::Transform* transform);
	void DrawVoxels(Comp::Voxels* voxels, Comp::VoxelDrawable* voxelDrawable, Comp::Transform* transform);
	glm::mat4 MatrixFromTransform(const Comp::Transform* transform);
};


}
}


#endif /* INCLUDES_GRAPHICS_H_ */
