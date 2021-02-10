#include <Windows.h>
#include <WinUser.h>
#include <Pch.hpp>
#include "InputManager.hpp"
#include "AtomEngine.hpp"

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

void InputManager::update()
{
	memcpy(mPrevKeyState, mCurrentKeyState, sizeof(mCurrentKeyState));

	if (!GetKeyboardState(mCurrentKeyState)) {
		ATOM_ERROR("InputManager : update : Keyboard State Not Loaded");
	}
}


bool InputManager::isKeyTriggered(unsigned int keycode)
{
	return (mCurrentKeyState[keycode] & 0x80) && !(mPrevKeyState[keycode] & 0x80);
}


bool InputManager::isKeyPressed(unsigned int keycode)
{
	return (mCurrentKeyState[keycode] & 0x80) && (mPrevKeyState[keycode] & 0x80);
}


bool InputManager::isKeyReleased(unsigned int keycode)
{
	return !(mCurrentKeyState[keycode] & 0x80) && (mPrevKeyState[keycode] & 0x80);
}
