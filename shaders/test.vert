#version 140 core
#extension GL_ARB_explicit_attrib_location : require

layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
