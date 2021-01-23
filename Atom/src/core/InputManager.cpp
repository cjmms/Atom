#include<Pch.hpp>

#include "InputManager.hpp"
#include "Event.hpp"
#include "EventManager.hpp"

extern EventManager gpEventManager;

void InputCallBack::update(GLFWwindow* win)
{
	
}

void InputCallBack::init(GLFWwindow* win)
{
	glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mod)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				//Broacast Key Triggered Event with key
				Event e(EventID::E_WINDOW_KEY_TRIGGERED);
				e.setParam<int>(P_WINDOW_KEY_TRIGGERED_KEYCODE, key);
				gpEventManager.sendEvent(e);
				break;
			}
			case GLFW_REPEAT:
			{
				//Broacast Key Pressed Event with key
				Event e(EventID::E_WINDOW_KEY_PRESSED);
				e.setParam<int>(P_WINDOW_KEY_PRESSED_KEYCODE, key);
				gpEventManager.sendEvent(e);
				break;
			}
			case GLFW_RELEASE:
			{
				//Broacast Key Released Event with key
				Event e(EventID::E_WINDOW_KEY_RELEASED);
				e.setParam<int>(P_WINDOW_KEY_RELEASED_KEYCODE, key);
				gpEventManager.sendEvent(e);
				break;
			}
			}
		});
}