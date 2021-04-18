/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		InputManager.cpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Input Manager - various input logics + stores current and prev state of keyboar and mouse
* @date		2021-02-03
*/

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

	mCurrentMouseXPos = 0.0;
	mCurrentMouseYPos = 0.0;
	mPreviousMouseXPos = 0.0;
	mPreviousMouseYPos = 0.0;
}



void InputManager::init()
{
	bool isLoaded = GetKeyboardState(mCurrentKeyState);
	if (!isLoaded)
	{
		ATOM_ERROR("Keyboard State Not Loaded - INIT");
	}

	glfwGetCursorPos(ae.mGraphicsManager->getWindow(), &mCurrentMouseXPos, &mCurrentMouseYPos);
	{
		//ATOM_INFO("Mouse Position loaded");
	}
}

void InputManager::update()
{
	memcpy(mPrevKeyState, mCurrentKeyState, sizeof(mCurrentKeyState));

	if (!GetKeyboardState(mCurrentKeyState)) {
		ATOM_ERROR("InputManager : update : Keyboard State Not Loaded");
	}

	mPreviousMouseXPos = mCurrentMouseXPos;
	mPreviousMouseYPos = mCurrentMouseYPos;

	glfwGetCursorPos(ae.mGraphicsManager->getWindow(), &mCurrentMouseXPos, &mCurrentMouseYPos);
	{
		//ATOM_INFO("Mouse Position updated")
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

std::pair<double, double> InputManager::getCursorPosChange()
{
	std::pair<double, double> dPosition;

	dPosition.first = mCurrentMouseXPos - mPreviousMouseXPos;
	dPosition.second = mCurrentMouseYPos - mPreviousMouseYPos;

	return dPosition;
}

std::pair<double, double> InputManager::getCursorPos()
{
	std::pair<double, double> dPosition;

	dPosition.first = mCurrentMouseXPos;
	dPosition.second = mCurrentMouseYPos;

	return dPosition;
}