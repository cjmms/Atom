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

	void startGame();
	void loadNextLevel();
	void loadPreviosLevel();

	void unload();

	void save();

	inline void restartCurrentLevel() { restartLevel = true; }

private:
	void load(int level);
	void load(string filepath);

	void loadCharacters();


private:
	bool restartLevel = false;
	bool enterNextLevel = false;
	bool enterPreviousLevel = false;

	int level = 0;

	//from map json, -1: no timer, >0: enter next level after the time
	double levelTime;	
	double levelStartTime;

};