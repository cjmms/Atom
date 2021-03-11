#pragma once

#include "Pch.hpp"
#include "utils/Log.hpp"
#include "GraphicsManager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// callback function for window resizing, hidden from any other files
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
	glfwSetWindowSize(window, (int)width, (int)height);
	glViewport(0, 0, width, height);
}


void GraphicsManager::init() {
	title = APPNAME;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;

	// Initialize the library 
	if (!glfwInit()) {
		ATOM_ERROR("Graphics : Failed to initialize glfw");
	}

	// window hints
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Create a windowed mode window and its OpenGL context
	mWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
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
	width = w;
	height = h;
	glfwSetWindowSize(mWindow, (int)width, (int)height);
	glViewport(0, 0, width, height);
}


void GraphicsManager::printInfo() const
{
	ATOM_INFO("Graphics: OpenGL version: {}", glGetString(GL_VERSION));
	ATOM_INFO("Graphics: OpenGL renderer: {}", glGetString(GL_RENDERER));
	ATOM_INFO("Graphics: Width: {}", width);
	ATOM_INFO("Graphics: Height: {}", height);
	ATOM_INFO("Graphics: Title: {}", title);
}

void GraphicsManager::getWindowSize(int& width, int& height)
{
	width = this->width;
	height = this->height;
}

