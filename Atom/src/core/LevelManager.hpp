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

	void load(int level);
	void loadNextLevel();

	void unload();

	void save();

private:
	void load(string filepath);

	void loadCharacters();

private:
	bool restartLevel = false;
	bool enterNextLevel = false;

	int level = 1;	//1-base level
};