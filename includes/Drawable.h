/**
 * Drawable.h
 *
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_


/* INCLUDES */
#include <string>
#include "Vec.h"

namespace TF
{
namespace Util
{


// Material struct
struct Material
{
	vec3<float> ambient = vec3<float>(1.0f, 1.0f, 1.0f);
	vec3<float> diffuse = vec3<float>(1.0f, 1.0f, 1.0f);
	vec3<float> specular = vec3<float>(1.0f, 1.0f, 1.0f);
	float rough = 32.0f;
};


// Drawable struct
struct Drawable
{
	std::string modelName = "";
	std::string shaderName = "";
	Material material;
};


}
}

#endif /* DRAWABLE_H_ */
