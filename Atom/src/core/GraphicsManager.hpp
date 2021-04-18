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
		if (!mFullscreen) {
			LevelWidth = SCREEN_WIDTH;
			LevelHeight = SCREEN_HEIGHT;

			WindowWidth = mode->width;
			WindowHeight = mode->height;


			glfwSetWindowPos(mWindow, 0, 0);
			glfwSetWindowMonitor(mWindow, monitor, 0, 0, WindowWidth, WindowHeight, mode->refreshRate);
			glViewport(fabsf((mode->width - mode->height) / 2), 0, mode->height, mode->height);
			mFullscreen = true;
		}

		ATOM_INFO("fullscreen");
		ATOM_INFO(mode->height);
		ATOM_INFO(mode->height);
		ATOM_INFO("end fullscreen");
	}
	inline void WindowMode()
	{
		//minimized = false;

		if (mFullscreen) {

			LevelWidth = SCREEN_WIDTH;
			LevelHeight = SCREEN_HEIGHT;

			WindowWidth = SCREEN_WIDTH;
			WindowHeight = SCREEN_HEIGHT;



			glViewport(0, 0, LevelWidth, LevelHeight);
			glfwSetWindowMonitor(mWindow, nullptr, 0, 0, WindowWidth, WindowHeight, FPS);
			glfwSetWindowPos(mWindow, 100, 100);
			mFullscreen = false;

		}
		ATOM_INFO("window");
		ATOM_INFO(mode->height);
		ATOM_INFO(mode->height);
		ATOM_INFO("end window");
	}

	GLFWwindow* mWindow = NULL;
	GLFWmonitor* monitor;
	const GLFWvidmode* mode;

	bool mFullscreen = true;
	bool minimized = false;

	string title;


	unsigned int WindowWidth;
	unsigned int WindowHeight;

	unsigned int LevelWidth;
	unsigned int LevelHeight;
};

