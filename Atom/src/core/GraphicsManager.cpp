/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		GraphicsManager.cpp
* @author	Xingyu Wang
* @brief	Graphics Manager - Contains logic for Rendering Entities
* @date		date 2021-01-27
*/

#pragma once

#include "Pch.hpp"
#include "utils/Log.hpp"
#include "GraphicsManager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "AtomEngine.hpp"

extern AtomEngine ae;

// callback function for window resizing, hidden from any other files
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{

}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	ae.mIsPaused = true;
}

void windowCloseCallback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, false);
	ae.mUIManager->closeWindow();
}

void windowFocusCallback(GLFWwindow* window, int focused)
{
	if (focused)
	{
		ae.mIsPaused = false;
	}
	else
	{
		ae.mIsPaused = true;
	}
}

void GraphicsManager::init() {

#ifdef DEBUG
	mFullscreen = false;
#endif // DEBUG

	title = APPNAME;

	LevelHeight = SCREEN_HEIGHT;
	LevelWidth = SCREEN_WIDTH;

	// Initialize the library 
	if (!glfwInit()) {
		ATOM_ERROR("Graphics : Failed to initialize glfw");
	}

	// window hints
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_RESIZABLE, false);

	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	WindowWidth = mode->width;
	WindowHeight = mode->height;


	// Create a windowed mode window and its OpenGL context
	if (mFullscreen) {
		mWindow = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
	}
	else {
		mWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), nullptr, nullptr);
	}


	if (!mWindow) {
		glfwTerminate();
		ATOM_ERROR("Graphics : Failed to create window");
	}

	// Make the window's context current 
	glfwMakeContextCurrent(mWindow);

	if (glewInit() != GLEW_OK) {
		ATOM_ERROR("Graphics : GLEW init error");
	}


	// when window size changes, object scales properly
	glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);
	glfwSetWindowSizeCallback(mWindow, windowResizeCallback);
	glfwSetWindowCloseCallback(mWindow, windowCloseCallback);
	glfwSetWindowFocusCallback(mWindow, windowFocusCallback);

	if (mFullscreen) {
		mFullscreen = !mFullscreen;
		FullScreenMode();
	}
	else {
		mFullscreen = !mFullscreen;
		WindowMode();
	}
	//else {
	//	glViewport(0, fabsf((WindowHeight - LevelHeight) / 2), LevelWidth, LevelHeight);
	//}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
}


void GraphicsManager::update()
{
	
}


void GraphicsManager::onEvent(Event& e) {}


void GraphicsManager::resize(unsigned int w, unsigned int h)
{

	if (w == 0 || h == 0)
	{
		ATOM_INFO("minimized");
		minimized = true;
		return;
	}

	WindowWidth = w;
	WindowHeight = h;

	if (minimized)
	{
		if (mFullscreen)
		{
			ATOM_INFO("minimized FullScreenMode");
			FullScreenMode();
		}
		else
		{
			ATOM_INFO("minimized WindowMode");
			WindowMode();
			minimized = false;
		}
		return;
	}

		int side = WindowWidth > WindowHeight ? WindowHeight : WindowWidth;

		glfwSetWindowSize(mWindow, (int)WindowWidth, (int)WindowHeight);

		float ratio = (float)WindowWidth / (float)WindowHeight;

		if (ratio > 1.0f)
			glViewport(fabsf((WindowWidth - LevelWidth) / 2), 0, LevelWidth, LevelHeight);

		if (ratio < 1.0f)
			glViewport(0, fabsf((WindowHeight - LevelHeight) / 2), LevelWidth, LevelHeight);


}


void GraphicsManager::printInfo() const
{
	ATOM_INFO("Graphics: OpenGL version: {}", glGetString(GL_VERSION));
	ATOM_INFO("Graphics: OpenGL renderer: {}", glGetString(GL_RENDERER));
	ATOM_INFO("Graphics: Window Width: {}", WindowWidth);
	ATOM_INFO("Graphics: Window Height: {}", WindowHeight);
	ATOM_INFO("Graphics: Title: {}", title);
}


