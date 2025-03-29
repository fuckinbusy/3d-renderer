#include "Engine.hpp"

Engine::Engine(int width, int height, float scale)
	: renderer(nullptr), inputManager(nullptr), scene(nullptr),
	isRunning(false), isInitialized(false)
{
	renderer = new Renderer(width, height, scale, RENDERER_DELAY_DEFAULT);
	scene = new Scene(renderer, width, height);
	inputManager = new InputManager(scene);
}

Engine::~Engine()
{
	Shutdown();
}

bool Engine::Initialize()
{
	std::cout << "Engine initialization started" << std::endl;

	// Loading 3D mesh objects
	scene->LoadMesh("3d/african_head.obj");

	std::cout << "Engine initialized. Everything has been loaded successfully." << std::endl;
	isInitialized = true;

	return isInitialized;
}

void Engine::Run()
{
	if (!isInitialized)
	{
		std::cerr << "Engine has not been initialized yet!" << std::endl;
		Shutdown();
		return;
	}

	isRunning = true;
	while (isRunning)
	{
		// Processing input
		inputManager->ProcessEvents(isRunning);
		inputManager->UpdateMousePosition();

		// Updating scene
		scene->Update();
	}
}

void Engine::Shutdown()
{
	// Cleaning up
	if (isInitialized)
	{
		std::cout << "Shutting down the engine..." << std::endl;
		delete renderer;
		delete scene;
		delete inputManager;

		isRunning = false;
		isInitialized = false;
		SDL_Quit();
	}
	else
	{
		std::cerr << "Engine has not been initialized yet!" << std::endl;
		exit(-1);
	}
	exit(0);
}
