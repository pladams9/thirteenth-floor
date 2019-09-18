#include <engine.h>
#include <graphics.h>
#include <vector>
#include <component.h>
#include <vertexListComp.h>
#include <shaderComp.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine(new TF::Graphics());

	// Add entities
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.0f,
		 0.2f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.1f,  0.1f, 0.0f,
		 0.8f, -0.7f, 0.0f
	};
	std::vector<int> elements = {
		0, 3, 2,
		1, 3, 4
	};
	TF::VertexListComp* v1 = new TF::VertexListComp(vertices, elements, 6);
	TF::ShaderComp* sh = new TF::ShaderComp("../shaders/test.vert", "../shaders/test.frag");

	std::vector<float> vertices2 = {
		-0.6f,  0.4f, 0.0f,
		-0.5f,  0.6f, 0.0f,
		-0.4f,  0.4f, 0.0f
	};
	std::vector<int> elements2 = {
		0, 1, 2
	};
	TF::VertexListComp* v2 = new TF::VertexListComp(vertices2, elements2, 3);
	engine.AddEntity({sh, v1});
	engine.AddEntity({sh, v2});


	// Run main loop
	engine.MainLoop();

	return 0;
}
