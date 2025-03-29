#pragma once
#include <iostream>
#include "SDL3/SDL.h"
#include "Scene.hpp"

class InputManager
{
public:
	InputManager(Scene* scene);
	~InputManager();

	void ProcessEvents(bool& isRunning);
	void UpdateMousePosition();

	float GetMouseX() const { return mouseX; }
	float GetMouseY() const { return mouseY; }

private:
	Scene* scene;
	float mouseX, mouseY;

	void MouseWheelHandler(SDL_MouseWheelEvent& mwEvent);
	void KeyboardInputHandlerD(SDL_Keycode key, bool& isRunning);
	void KeyboardInputHandlerU(SDL_Keycode key, bool& isRunning);
	void MouseMotionHandler(SDL_MouseMotionEvent& mmEvent);
};

