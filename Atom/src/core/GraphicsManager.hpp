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

	void SetWindowSize(int &width, int &height);

	inline unsigned int GetWindowWidth() const { return width; }
	inline unsigned int GetWindowHeight() const { return height; }

	inline void FullScreenMode()
	{
		if (!mFullscreen) {
			monitor = glfwGetPrimaryMonitor();
			mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			resize(mode->width, mode->height);
			mFullscreen = true;
		}
	}
	inline void WindowMode()
	{
		if (mFullscreen) {
			// whenever exit full screenmode, set it to fixed size, fixed position
			// position: 100, 100
			// size: 800, 800
			glfwSetWindowMonitor(mWindow, nullptr, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, FPS);
			resize(width, height);
			mFullscreen = false;
		}
	}

private:
	GLFWwindow* mWindow = NULL;
	GLFWmonitor* monitor;
	const GLFWvidmode* mode;

	bool mFullscreen = true;

	string title;
	unsigned int width;
	unsigned int height;
};

