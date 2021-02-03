#include <Windows.h>
#include <WinUser.h>
#include <Pch.hpp>
#include "InputManager.hpp"
#include "Event.hpp"
#include "EventManager.hpp"
#include "AtomEngine.hpp"
#include <memory.h>

extern AtomEngine ae;

InputManager::InputManager()
{
	memset(mCurrentKeyState, '\0', sizeof(mCurrentKeyState));
	memset(mPrevKeyState, '\0', sizeof(mCurrentKeyState));
}



void InputManager::init()
{
	bool isLoaded = GetKeyboardState(mCurrentKeyState);
	if (!isLoaded)
	{
		ATOM_ERROR("Keyboard State Not Loaded - INIT");
	}
}

//void InputManager::init(GLFWwindow* win)
//{
//
//	glfwSetKeyCallback(win, [](GLFWwindow* window, int key, int scancode, int action, int mod)
//		{
//			switch (action)
//			{
//			case GLFW_PRESS:
//			{
//				//Broacast Key Triggered Event with key
//				Event e(EventID::E_WINDOW_KEY_TRIGGERED);
//				e.setParam<int>(P_WINDOW_KEY_TRIGGERED_KEYCODE, key);
//				gpEventManager.sendEvent(e);
//				break;
//			}
//			case GLFW_REPEAT:
//			{
//				//Broacast Key Pressed Event with key
//				Event e(EventID::E_WINDOW_KEY_PRESSED);
//				e.setParam<int>(P_WINDOW_KEY_PRESSED_KEYCODE, key);
//				gpEventManager.sendEvent(e);
//				break;
//			}
//			case GLFW_RELEASE:
//			{
//				//Broacast Key Released Event with key
//				Event e(EventID::E_WINDOW_KEY_RELEASED);
//				e.setParam<int>(P_WINDOW_KEY_RELEASED_KEYCODE, key);
//				gpEventManager.sendEvent(e);
//				break;
//			}
//			}
//		});
//}


void InputManager::update()
{
	memcpy(mPrevKeyState, mCurrentKeyState, sizeof(mCurrentKeyState));

	bool isLoaded = GetKeyboardState(mCurrentKeyState);
	if (!isLoaded)
	{
		ATOM_ERROR("Keyboard State Not Loaded - UPDATE");
	}
}


bool InputManager::isKeyTriggered(unsigned int keycode)
{
	if ((short)mCurrentKeyState[keycode] >= 128 && (short)mPrevKeyState[keycode] < 128)
	{
		ATOM_INFO("{} is triggered and value: {}", keycode, (short)mCurrentKeyState[keycode]);

		/*Event e(EventID::E_WINDOW_KEY_TRIGGERED);
		e.setParam<int>(P_WINDOW_KEY_TRIGGERED_KEYCODE, keycode);
		ae.mEventManager->sendEvent(e);*/

		return TRUE;
	}

	return FALSE;
}


bool InputManager::isKeyPressed(unsigned int keycode)
{
	if ((short)mCurrentKeyState[keycode] >= 128 && (short)mPrevKeyState[keycode] >= 128)
	{
		ATOM_TRACE("{} is pressed and value: {}", keycode, (short)mCurrentKeyState[keycode]);

		/*Event e(EventID::E_WINDOW_KEY_PRESSED);
		e.setParam<int>(P_WINDOW_KEY_PRESSED_KEYCODE, keycode);
		ae.mEventManager->sendEvent(e);*/

		return TRUE;
	}

	

	return FALSE;
}


bool InputManager::isKeyReleased(unsigned int keycode)
{
	if ((short)mCurrentKeyState[keycode] < 128 && (short)mPrevKeyState[keycode] >= 128)
	{
		ATOM_INFO("{} is relesed and value: {}", keycode, (short)mCurrentKeyState[keycode]);

		/*Event e(EventID::E_WINDOW_KEY_RELEASED);
		e.setParam<int>(P_WINDOW_KEY_RELEASED_KEYCODE, keycode);
		ae.mEventManager->sendEvent(e);*/

		return TRUE;
	}

	return FALSE;
}
