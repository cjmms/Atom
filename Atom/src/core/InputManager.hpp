/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		InputManager.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Input Manager - various input logics + stores current and prev state of keyboar and mouse
* @date		2021-02-03
*/

#pragma once

class InputManager
{
public:
	InputManager();
	void init();
	void update();
	bool isKeyTriggered(unsigned int keycode);
	bool isKeyPressed(unsigned int keycode);
	bool isKeyReleased(unsigned int keycode);
	std::pair<double, double> getCursorPosChange();
	std::pair<double, double> getCursorPos();

public:
	unsigned char mCurrentKeyState[256];
	unsigned char mPrevKeyState[256];

	double mCurrentMouseXPos;
	double mCurrentMouseYPos;
	double mPreviousMouseXPos;
	double mPreviousMouseYPos;
};