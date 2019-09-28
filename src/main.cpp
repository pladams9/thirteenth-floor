#include <Engine.h>
#include <EntityBuilders.h>
#include <systems/graphics.h>
#include <systems/EventLogger.h>
#include <systems/KeyboardInput.h>
#include <systems/Logic.h>
#include <systems/Movement.h>
#include <systems/SDLEventHandler.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine;

	// Add systems
	engine.AddSystem(new TF::Sys::SDLEventHandler(&engine), 0);
	engine.AddSystem(new TF::Sys::Graphics(&engine, 640, 480, "SUPER AWESOME TEST WINDOW"), 50);
	engine.AddSystem(new TF::Sys::LogicSystem(&engine), 10);
	engine.AddSystem(new TF::Sys::EventLogger(&engine), 10);
	engine.AddSystem(new TF::Sys::KeyboardInput(&engine), 10);
	engine.AddSystem(new TF::Sys::MovementSystem(&engine), 15);

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
