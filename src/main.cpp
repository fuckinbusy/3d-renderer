#include "Engine.hpp"

int main()
{
	Engine engine(1080, 1080, 1.0f);

	engine.Initialize();
	engine.Run();
	engine.Shutdown();
	return 0;
}