#include <builders.h>
#include <engine.h>
#include <systems/graphics.h>
#include <systems/logic.h>
#include <systems/SDLEvents.h>
#include <systems/EventLogger.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine;

	// Add systems
	engine.AddSystem(new TF::SDLEventSystem(&engine), 0);
	engine.AddSystem(new TF::Graphics(&engine, 640, 480, "SUPER AWESOME TEST WINDOW"), 2);
	engine.AddSystem(new TF::LogicSystem(&engine), 1);
	engine.AddSystem(new TF::EventLoggerSystem(&engine), 1);

	// Add entities
	for(int i = 0; i < 20; ++i)
	{
		engine.AddEntity(TF::Create::Cube());
	}
	engine.AddEntity(TF::Create::Camera());

	// Run main loop
	engine.Start();

	return 0;
}
