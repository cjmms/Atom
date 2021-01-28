/*
* @file		Graphics.hpp
* @author	Abhikalp Unakal
* @brief	platform specific graphics implementation for windows + glfw 
* @date		2021-01-27
*/


#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "core/Types.hpp"
#include "core/Event.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowData {
public:
	string title;
	unsigned int width;
	unsigned int height;
};

class Graphics {
public:
	void init();
	void update();
	void onEvent(Event& e);
	void resize(unsigned int w, unsigned int h);
	string getWindowTitle();
	void setWindowTitle(string s);
	void printInfo();
	bool shouldWindowClose();
	GLFWwindow* getWindow();
private:
	GLFWwindow* mWindow = NULL;
	WindowData mWindowData;
};
#endif // !GRAPHICS_HPP
