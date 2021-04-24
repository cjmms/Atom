/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		ParticleEffect.hpp
* @author	Xingyu Wang
* @brief	Particle Initialisation & Rendering using Compute Shader
* @date		2021-04-07
*/

#pragma once

#include "core/Shader.hpp"
#include <vector>
#include <chrono>
#include <random>
// This is a 2D Particle system

using namespace std::chrono;


float gen_random(float min, float max);


struct Particle
{
	Particle(glm::vec2 position, glm::vec2 velocity, float scale, float time);

	glm::vec2 position;
	glm::vec2 velocity;
	float scale;
	float duration;
};

enum AREA_MODE
{
	CIRCLE,
	SQUARE
};

enum DIR_MODE
{
	CIRCULAR,
	LINEAR,
	//CIRCULAR_SECTOR		// have bug
};


struct ParticleConfig
{
	ParticleConfig(float numOfParticles, float scale, glm::vec2 time)
		: numOfParticles(numOfParticles), scale(scale), time(time) {}

	float numOfParticles;
	float scale;
	glm::vec2 time;
};


struct SpawnConfig
{
	SpawnConfig(glm::vec2 center, float length, AREA_MODE mode)
		:areaCenter(center), length(length), mode(mode) {}

	glm::vec2 areaCenter;
	float length;
	AREA_MODE mode;
};


struct MoveConfig
{
	MoveConfig(glm::vec2 dir, float magnitude, DIR_MODE mode)
		:direction(glm::normalize(dir)), magnitude(magnitude), mode(mode) {}

	// add an offset prevent vec2(0.0, 0.0)
	MoveConfig(glm::vec2 dir, float angle, float magnitude, DIR_MODE mode)
		:direction(glm::normalize(dir)), magnitude(magnitude), mode(mode), angle(angle) {}

	glm::vec2 direction;
	float magnitude;
	float angle;
	DIR_MODE mode;
};




class ParticleEffect
{

public:
	ParticleEffect(SpawnConfig spawnConfig, MoveConfig moveConfig, ParticleConfig paConfig);

	void Init();
	void Draw(glm::vec2& position);
	void Destory();
	void Print();


private:
	unsigned int VAO;
	unsigned int SSBO;

	time_point<steady_clock> lastFrameTime;
	time_point<steady_clock> start;

	Shader RenderShader;
	Shader ComputeShader;

	std::vector<Particle> Particles;

	glm::vec2 spawnCenter;

public:
	glm::vec3 position = glm::vec3{0.0f,0.0f,0.0f};
};

