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

public:
	unsigned char mCurrentKeyState[256];
	unsigned char mPrevKeyState[256];
};