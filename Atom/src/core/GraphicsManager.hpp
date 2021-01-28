/*
* @file		GraphicsManager.hpp
* @author	Abhikalp Unakal
* @brief	High level graphics initialization api 
* @date		2021-01-26
*/

#ifndef GRAPHICSMANAGER_HPP
#define GRAPHICSMANAGER_HPP
#include "Pch.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

// if windows
#ifdef _WIN64
#include "platform/windows/Graphics.hpp"
#endif

// if macos
#ifdef __APPLE__
#include "platform/macos/Graphics.hpp"
#endif


class GraphicsManager {
public:
	void init() {
		gfx.init();
	}
	void update() {
		gfx.update();
	}
	void onEvent(Event& e) {
		gfx.onEvent(e);
	}
	void resize(unsigned int w, unsigned int h) {
		gfx.resize(w, h);
	}
	string getWindowTitle() {
		return gfx.getWindowTitle();
	}
	void setWindowTitle(string s) {
		gfx.setWindowTitle(s);
	}
	void printInfo() {
		gfx.printInfo();
	}
	bool shouldWindowClose() {
		return gfx.shouldWindowClose();
	}

	//private:
public:
	Graphics gfx;
};

#endif GRAPHICSMANAGER_HPP