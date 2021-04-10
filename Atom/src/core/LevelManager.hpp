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

	void loadDefaultFile();

	inline void restartWholeGame() { restartGame = true; }

	inline void restartCurrentLevel() { restartLevel = true; }

	float lerp10(float a, float b, float t, float lo, float hi);
	float lerp01(float a, float b, float t, float lo, float hi);

	inline int GetCurrentLevelNumber() { return level; }

private:
	void load(int level);
	void load(string filepath);

	void loadCharacters(string charloc);
	bool screenByPass();


private:
	bool restartGame = false;
	bool restartLevel = false;
	bool enterNextLevel = false;
	bool enterPreviousLevel = false;
	
	int level = 0;
	std::vector<string> levelPaths;

	//from map json, -1: no timer, >0: enter next level after the time
	double levelTime;	
	double levelStartTime;


public:
	float level_alpha = 1.0f;
	float level_alpha_end = 0.0f;
	float fade_out_timer = 0.0f;
	float fade_in_timer = 0.0f;
	string levelstring = "";
	bool fade_in_level = true;
	

};