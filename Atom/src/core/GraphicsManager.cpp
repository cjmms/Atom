#pragma once

#include "Pch.hpp"
#include "utils/Log.hpp"
#include "GraphicsManager.hpp"

// callback function for window resizing, hidden from any other files
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
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
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	//glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
}


void GraphicsManager::update()
{
	//glfwSwapBuffers(mWindow);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_DEPTH_BUFFER_BIT);
	int display_w, display_h;
	glfwGetFramebufferSize(mWindow, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glfwSwapBuffers(mWindow);
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