#pragma once
#include "Pch.hpp"
#include "core/Event.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GraphicsManager {
public:
	~GraphicsManager() {
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

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


	inline unsigned int GetWindowWidth() const 
	{ 
		return WindowWidth; 
	}
	inline unsigned int GetWindowHeight() const 
	{ 
		return WindowHeight; 
	}

	inline unsigned int GetLevelWidth() const { return LevelWidth; }
	inline unsigned int GetLevelHeight() const { return LevelHeight; }


	inline void FullScreenMode()
	{
		glfwSetWindowPos(mWindow, 0, 0);
		resize(mode->width, mode->height);
	}
	inline void WindowMode()
	{
		glfwSetWindowPos(mWindow, 100, 100);
		resize(SCREEN_WIDTH + 1, SCREEN_HEIGHT);
	}

private:
	GLFWwindow* mWindow = NULL;
	GLFWmonitor* monitor;
	const GLFWvidmode* mode;

	bool mFullscreen = true;

	string title;


	unsigned int WindowWidth;
	unsigned int WindowHeight;

	unsigned int LevelWidth;
	unsigned int LevelHeight;
};

