#pragma once

//#include "GLFW/glfw3.h"

class InputManager
{
public:
	InputManager();
	void init();
	//void init(GLFWwindow* win);
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