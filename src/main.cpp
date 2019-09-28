#include <Engine.h>
#include <EntityBuilders.h>
#include <systems/graphics.h>
#include <systems/SDLEvents.h>
#include <systems/EventLogger.h>
#include <systems/KeyboardController.h>
#include <systems/Logic.h>
#include <systems/Movement.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine;

	// Add systems
	engine.AddSystem(new TF::SDLEventSystem(&engine), 0);
	engine.AddSystem(new TF::Graphics(&engine, 640, 480, "SUPER AWESOME TEST WINDOW"), 50);
	engine.AddSystem(new TF::LogicSystem(&engine), 10);
	engine.AddSystem(new TF::EventLoggerSystem(&engine), 10);
	engine.AddSystem(new TF::KeyboardControllerSystem(&engine), 10);
	engine.AddSystem(new TF::MovementSystem(&engine), 15);

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
