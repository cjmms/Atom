#include "Pch.hpp"
#include "Graphics.hpp"
#include "utils/Log.hpp"

void Graphics::init(){
	mWindowData.title = APPNAME;
	mWindowData.width = SCREEN_WIDTH;
	mWindowData.height = SCREEN_HEIGHT;

	// Initialize the library 
	if (!glfwInit()) {
		ATOM_ERROR("Graphics : Failed to initialize glfw");
	}

	// window hints
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// Create a windowed mode window and its OpenGL context
	mWindow = glfwCreateWindow(mWindowData.width, mWindowData.height, mWindowData.title.c_str(), NULL, NULL);
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

void Graphics::update(){
	glfwSwapBuffers(mWindow);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::onEvent(Event& e){
}

void Graphics::resize(unsigned int w, unsigned int h){
	mWindowData.width = w;
	mWindowData.height = h;
	glfwSetWindowSize(mWindow, (int)mWindowData.width, (int)mWindowData.height);
	glViewport(0, 0, mWindowData.width, mWindowData.height);
}

string Graphics::getWindowTitle(){
	return mWindowData.title;
}

void Graphics::setWindowTitle(string s){
	glfwSetWindowTitle(mWindow, mWindowData.title.c_str());
}

void Graphics::printInfo(){
	ATOM_INFO("Graphics: OpenGL version: {}", glGetString(GL_VERSION));
	ATOM_INFO("Graphics: OpenGL renderer: {}", glGetString(GL_RENDERER));
	ATOM_INFO("Graphics: Width: {}", mWindowData.width);
	ATOM_INFO("Graphics: Height: {}", mWindowData.height);
	ATOM_INFO("Graphics: Title: {}", mWindowData.title);
}

bool Graphics::shouldWindowClose(){
	return glfwWindowShouldClose(mWindow);
}

GLFWwindow* Graphics::getWindow() {
	return mWindow;
}
