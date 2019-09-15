#include <engine.h>
#include <graphics.h>

int main( int argc, char* args[] )
{
	TF::Engine engine(new TF::Graphics());

	engine.mainLoop();

	return 0;
}
