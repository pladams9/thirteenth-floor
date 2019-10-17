/* INCLUDES */
#include <engine/Engine.h>
#include "Logger.h"
#include <EntityBuilders.h>
#include <systems/EventLogger.h>
#include <systems/KeyboardInput.h>
#include <systems/Logic.h>
#include <systems/Movement.h>
#include <systems/Physics.h>
#include <systems/OpenGLRenderer.h>
#include <systems/SDLWrapper.h>
#include "components/LightSource.h"
#include "Vec.h"


/* FUNCTION DECLARATIONS */
void BuildRingScene(TF::Engine& engine);


/* MAIN */
int main(int argc, char* args[])
{
	// Set logger threshold
	#ifdef DEBUG_LOGGING
	TF::LOGGER().SetLogThreshold(TF::DEBUG, TF::INFO);
	#else
	TF::LOGGER().SetLogThreshold(TF::INFO, TF::NONE);
	#endif

	TF::LOGGER().Log(TF::DEBUG, "Starting main()");

	// Create Engine
	TF::Engine engine;

	// Build Scene
	BuildRingScene(engine);

	// Run engine loop
	engine.Start();

	TF::LOGGER().Log(TF::DEBUG, "Finishing main()");
	return 0;
}


/* FUNCTION DEFINITIONS */
void BuildRingScene(TF::Engine& engine)
{
	// Add systems
	TF::LOGGER().Log(TF::DEBUG, "Creating systems");
	engine.AddSystem(new TF::Sys::SDLWrapper(&engine));
	engine.AddSystem(new TF::Sys::OpenGLRenderer(&engine, 1366, 768));
	engine.AddSystem(new TF::Sys::KeyboardInput(&engine));
	engine.AddSystem(new TF::Sys::MovementSystem(&engine));
	engine.AddSystem(new TF::Sys::Physics(&engine));
	TF::LOGGER().Log(TF::DEBUG, "Finished creating systems");

	// Add entities
	TF::LOGGER().Log(TF::DEBUG, "Creating entities");

	engine.AddEntity(TF::Create::VoxelChunk(TF::VoxGen::Ring));
	engine.AddEntity(TF::Create::Camera());

	using TF::Util::vec3d;
	TF::Comp::Light l;
	l.lightType = TF::Comp::DIRECTIONAL;
	// Sun
	l.ambient = vec3d(0.3, 0.3, 0.2);
	l.diffuse = vec3d(1.0, 1.0, 0.75);
	l.specular = vec3d(1.0, 1.0, 1.0);
	l.direction = vec3d(0.5, -1.0, 0.0);
	engine.AddEntity(TF::Create::Light(l));
	// Ground reflection
	l.ambient = vec3d(0);
	l.diffuse = vec3d(0.1, 0.1, 0.2);
	l.specular = vec3d(0.1, 0.1, 0.2);
	l.direction = vec3d(0.5, 1.0, 0.0);
	engine.AddEntity(TF::Create::Light(l));

	TF::LOGGER().Log(TF::DEBUG, "Finished creating entities");
}
