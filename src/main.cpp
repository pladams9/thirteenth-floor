#include <builders.h>
#include <engine.h>
#include <systems/graphics.h>
#include <systems/logic.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine;

	// Add systems
	engine.AddSystem(new TF::Graphics(&engine, 640, 480, "SUPER AWESOME TEST WINDOW"));
	engine.AddSystem(new TF::LogicSystem(&engine));

	// Add entities
	for(int i = 0; i < 20; ++i)
	{
		engine.AddEntity(TF::Create::Cube());
	}
	engine.AddEntity(TF::Create::Camera());

	// Run main loop
	engine.MainLoop();

	return 0;
}
