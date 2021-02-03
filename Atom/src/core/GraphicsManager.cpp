#pragma once

#include "Pch.hpp"
#include "utils/Log.hpp"
#include "GraphicsManager.hpp"

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
}


void GraphicsManager::update()
{
	glfwSwapBuffers(mWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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