#pragma once
#include "Pch.hpp"
#include "core/Event.hpp"

class LevelManager
{
public:
	LevelManager();
	void init();
	void update();
	void onEvent(Event& e);

private:
	bool restartLevel = false;

};