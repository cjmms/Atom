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
	ParticleConfig(float numOfParticles = 50, float scale = 0.1f, glm::vec2 time = glm::vec2{0.1f,2.0f})
		: numOfParticles(numOfParticles), scale(scale), time(time) {}

	float numOfParticles;
	float scale;
	glm::vec2 time;
};


struct SpawnConfig
{
	SpawnConfig(glm::vec2 center = glm::vec2{0.0f,0.0f}, float length = 0.01f, AREA_MODE mode=AREA_MODE::CIRCLE)
		:areaCenter(center), length(length), mode(mode) {}

	glm::vec2 areaCenter;
	float length;
	AREA_MODE mode;
};


struct MoveConfig
{
	MoveConfig(glm::vec2 dir = glm::vec2{0.0f,0.0f}, float magnitude=0.001f, DIR_MODE mode=DIR_MODE::CIRCULAR)
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

