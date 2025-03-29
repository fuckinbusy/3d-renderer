#pragma once
#include "Renderer.hpp"
#include "InputManager.hpp"
#include "Scene.hpp"

class Engine
{
public:
	Engine(int width, int height, float scale);
	~Engine();

	// This function should be used before running the Engine
	bool Initialize();
	void Run();
	void Shutdown();

private:
	Renderer* renderer;
	InputManager* inputManager;
	Scene* scene;

	bool isInitialized;
	bool isRunning;
};

