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
	ae.mGraphicsManager->resize(width, height);
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	ae.mGraphicsManager->resize(width, height);
	ae.mIsPaused = true;
}

void windowCloseCallback(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, false);
	ae.mUIManager->closeWindow();
}

void GraphicsManager::init() {

	mFullscreen = true;

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
	//mWindow = glfwCreateWindow(800, 800, title.c_str(), nullptr, nullptr);
	mWindow = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
	//mWindow = glfwCreateWindow(mode->width, mode->height, title.c_str(), nullptr, nullptr);


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

	glViewport(fabsf((mode->width - mode->height) / 2), 0, mode->height, mode->height);
	//glViewport(fabsf((800 - 800) / 2), 0, 800, 800);

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
	WindowWidth = w;
	WindowHeight = h;

	int side = WindowWidth > WindowHeight ? WindowHeight : WindowWidth;

	//LevelWidth = side;
	//LevelHeight = side;

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


