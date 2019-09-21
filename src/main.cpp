#include <engine.h>
#include <graphics.h>
#include <factory.h>

int main( int argc, char* args[] )
{
	// Create Engine
	TF::Engine engine(new TF::Graphics());

	// Add entity
	engine.AddEntity(TF::Factory::Cube());

	// Run main loop
	engine.MainLoop();

	return 0;
}
