#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"

extern AtomEngine ae;

void ControllerSystem::init()
{
	ae.addEventListener(EventID::E_WINDOW_KEY_TRIGGERED, [this](Event& e) 
		{
			this->onEvent(e);
		});

	ae.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e)
		{
			this->onEvent(e);
		});

	ae.addEventListener(EventID::E_WINDOW_KEY_RELEASED, [this](Event& e)
		{
			this->onEvent(e);
		});
}
void ControllerSystem::update()
{

}
void ControllerSystem::onEvent(Event& e)
{
	if (e.getType() == EventID::E_WINDOW_KEY_TRIGGERED)
	{
		switch (e.getParam<int>(P_WINDOW_KEY_TRIGGERED_KEYCODE))
		{
		case (VK_UP):
			//Jump
			break;
		default:
			break;
		}
	}

	else if (e.getType() == EventID::E_WINDOW_KEY_PRESSED)
	{
		switch (e.getParam<int>(P_WINDOW_KEY_PRESSED_KEYCODE))
		{
		case (VK_LEFT):
			//Move left
			break;
		case (VK_RIGHT):
			//Move right
			break;
		default:
			break;
		}
	}

	else if (e.getType() == EventID::E_WINDOW_KEY_RELEASED)
	{
		switch (e.getParam<int>(P_WINDOW_KEY_RELEASED_KEYCODE))
		{
		case (VK_ESCAPE):
			//Quit
			break;
		default:
			break;
		}
	}
}