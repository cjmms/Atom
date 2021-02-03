#pragma once
#include "Pch.hpp"
#include "core/Event.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GraphicsManager {
public:
	void init();

	// swap framebuffer, clean framebuffer
	void update();

	void onEvent(Event& e);

	void resize(unsigned int w, unsigned int h);

	inline string getWindowTitle() const { return title; }

	inline void setWindowTitle(string s) { glfwSetWindowTitle(mWindow, title.c_str()); }

	void printInfo() const;

	inline bool shouldWindowClose() { return glfwWindowShouldClose(mWindow); }

	inline GLFWwindow* getWindow() { return mWindow; }


private:
	GLFWwindow* mWindow = NULL;

	string title;
	unsigned int width;
	unsigned int height;
};

