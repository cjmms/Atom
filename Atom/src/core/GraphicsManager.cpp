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
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;

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
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;

	// Initialize the library 
	if (!glfwInit()) {
		ATOM_ERROR("Graphics : Failed to initialize glfw");
	}

	// window hints
	glfwWindowHint(GLFW_DECORATED, true);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	monitor = glfwGetPrimaryMonitor();
	mode = glfwGetVideoMode(monitor);

	// Create a windowed mode window and its OpenGL context
	//mWindow = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
	mWindow = glfwCreateWindow(mode->width, mode->height, title.c_str(), nullptr, nullptr);


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
	std::cout << "origin width: " << width << std::endl;
	std::cout << "origin height: " << height << std::endl;

	width = w;
	height = h;


	int side = width > height ? height : width;

	std::cout << "side: " << side << std::endl;


	glfwSetWindowSize(mWindow, (int)width, (int)height);

	float ratio = (float)width / (float)height;

	std::cout << "ratio: " << ratio << std::endl;

	if (ratio > 1.0f)
		glViewport(fabsf((width - side) / 2), 0, side, side);

	if (ratio < 1.0f)
		glViewport(0, fabsf((height - side) / 2), side, side);

	//if (ratio = 1.0f)
		//glViewport(0, 0, side, side);
}


void GraphicsManager::printInfo() const
{
	ATOM_INFO("Graphics: OpenGL version: {}", glGetString(GL_VERSION));
	ATOM_INFO("Graphics: OpenGL renderer: {}", glGetString(GL_RENDERER));
	ATOM_INFO("Graphics: Width: {}", width);
	ATOM_INFO("Graphics: Height: {}", height);
	ATOM_INFO("Graphics: Title: {}", title);
}

void GraphicsManager::SetWindowSize(int& width, int& height)
{
	this->width = width;
	this->height = height;
}

