#include <Engine.h>
#include <EntityBuilders.h>
#include <systems/EventLogger.h>
#include <systems/KeyboardInput.h>
#include <systems/Logic.h>
#include <systems/Movement.h>
#include <systems/OpenGLRenderer.h>
#include <systems/SDLWrapper.h>

int main(int argc, char* args[])
{
	// Create Engine
	TF::Engine engine;

	// Add systems
	engine.AddSystem(new TF::Sys::SDLWrapper(&engine));
	engine.AddSystem(new TF::Sys::OpenGLRenderer(&engine, 1366, 768));
	engine.AddSystem(new TF::Sys::LogicSystem(&engine));
	engine.AddSystem(new TF::Sys::EventLogger(&engine));
	engine.AddSystem(new TF::Sys::KeyboardInput(&engine));
	engine.AddSystem(new TF::Sys::MovementSystem(&engine));

	// Add entities
	for(int i = 0; i < 300; ++i)
	{
		engine.AddEntity(TF::Create::Cube());
	}
	engine.AddEntity(TF::Create::Camera());

	// Run main loop
	engine.Start();

	return 0;
}
