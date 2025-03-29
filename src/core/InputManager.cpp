#include "InputManager.hpp"

InputManager::InputManager(Scene* scene)
	: mouseX(0.0f), mouseY(0.0f), scene(scene)
{
}

InputManager::~InputManager() {}

void InputManager::ProcessEvents(bool& isRunning)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;

			case SDL_EVENT_KEY_DOWN:
				KeyboardInputHandlerD(event.key.key, isRunning);
				break;

			case SDL_EVENT_KEY_UP:
				KeyboardInputHandlerU(event.key.key, isRunning);
				break;

			case SDL_EVENT_MOUSE_WHEEL:
				MouseWheelHandler(event.wheel);
				break;

			case SDL_EVENT_MOUSE_MOTION:
				MouseMotionHandler(event.motion);
				break;

			default:
				break;
		}
	}

	UpdateMousePosition();
}

void InputManager::UpdateMousePosition()
{
	SDL_GetMouseState(&mouseX, &mouseY);
}

void InputManager::MouseWheelHandler(SDL_MouseWheelEvent& mwEvent)
{
	Model& model = scene->GetModel();

	float scaleFactor = mwEvent.y / 10.0f;
	float modelScale = model.GetModelScale();
	float scale = modelScale + scaleFactor;

	if (std::fabs(scale) >= 3) scale = 3;

	float newModelScale = model.SetModelScale(scale);
	
	if (std::fabs(newModelScale) < 1e-6) newModelScale += scaleFactor * 2.0f;

	model.Scale(newModelScale);;

}

void InputManager::KeyboardInputHandlerD(SDL_Keycode key, bool& isRunning)
{
	switch (key)
	{
		case SDLK_ESCAPE:
			isRunning = false;
			break;

		// Rotating by arrows
		case SDLK_LEFT:
		{
			Model& m = scene->GetModel();
			m.SetModelAngles(m.GetAngleX(), m.GetAngleY() + 0.1f, m.GetAngleZ());
		}
		break;

		case SDLK_RIGHT:
		{
			Model& m = scene->GetModel();
			m.SetModelAngles(m.GetAngleX(), m.GetAngleY() - 0.1f, m.GetAngleZ());
		}
		break;

		case SDLK_UP:
		{
			Model& m = scene->GetModel();
			m.SetModelAngles(m.GetAngleX() + 0.1f, m.GetAngleY(), m.GetAngleZ());
		}
		break;

		case SDLK_DOWN:
		{
			Model& m = scene->GetModel();
			m.SetModelAngles(m.GetAngleX() - 0.1f, m.GetAngleY(), m.GetAngleZ());
		}
		break;

		// Scaling by "+" and "-"("=")
		case SDLK_EQUALS:
		{
			Model& model = scene->GetModel();
			float newScale = model.SetModelScale(model.GetModelScale() + model.GetScaleFactor());
			model.Scale(newScale);
		}
		break;

		case SDLK_MINUS:
		{
			Model& model = scene->GetModel();
			float newScale = model.SetModelScale(model.GetModelScale() - model.GetScaleFactor());
			model.Scale(newScale);
		}
		break;

		default:
			break;
	}
}

void InputManager::KeyboardInputHandlerU(SDL_Keycode key, bool& isRunning)
{
	switch (key)
	{
		default:
			break;
	}
}

void InputManager::MouseMotionHandler(SDL_MouseMotionEvent& mmEvent)
{
	const float sens = 0.001f;
	//std::cout << "State: " << mmEvent.state << std::endl;
	switch (mmEvent.state)
	{
		case SDL_BUTTON_LEFT:
		{
			//std::cout << "SDL_BUTTON_LEFT | " << "relx: " << mmEvent.xrel << " rely: " << mmEvent.yrel << std::endl;
			Model& m = scene->GetModel();
			m.SetModelAngles(m.GetAngleX() - mmEvent.yrel / 100.0f, m.GetAngleY() - mmEvent.xrel / 100.0f, m.GetAngleZ());
		}
		break;

		case SDL_BUTTON_X1:
		{
			//std::cout << "SDL_BUTTON_RIGHT | " << "relx: " << mmEvent.xrel << " rely: " << mmEvent.yrel << std::endl;
			Model& m = scene->GetModel();
			m.Translate( m.GetPosX() - mmEvent.xrel * sens, m.GetPosY() + mmEvent.yrel * sens, m.GetPosZ());
			//std::cout << "MouseX: " << GetMouseX() << "ModelX: " << m.GetPosX() << std::endl;
		}
		break;

		default:
			break;
	}
}
