/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ParticleEffect.cpp
* @author	Xingyu Wang
* @brief	Particle Initialisation & Rendering using Compute Shader
* @date		2021-04-07
*/

#include "Pch.hpp"
#include "ParticleEffect.hpp"
#include <sstream>
#include <string>
#include <iostream>
#include <cmath>
#include "core/AtomEngine.hpp"
#include "components/AllComponents.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern AtomEngine ae;


void ParticleEffect::Init()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	{ // Particle SSBO
		glGenBuffers(1, &SSBO);
		glBindBuffer(GL_ARRAY_BUFFER, SSBO);
		glBufferData(GL_ARRAY_BUFFER, Particles.size() * sizeof(Particle), &Particles[0], GL_STREAM_DRAW);
	}

	{ // Setup Vertex Attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);


		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);	// position
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 2)); // velocity
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 4)); // scale
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (GLvoid*)(sizeof(float) * 5)); // duration


		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glVertexAttribDivisor(3, 1);
	}

	glBindVertexArray(0);


	// compute shader unifroms
	start = steady_clock::now();
	lastFrameTime = start;

	float time = duration_cast<duration<float>>(steady_clock::now() - lastFrameTime).count();
	ComputeShader.SetFloat("time", time);

	// render shader uniforms
	RenderShader.SetInt("vertex_count", this->Particles.size());
}



void ParticleEffect::Draw(glm::vec2& position)
{
	time_point<steady_clock> now = steady_clock::now();
	float time = duration_cast<duration<float>>(now - lastFrameTime).count();
	//std::cout << "delta time: " << time << std::endl;
	//std::cout << "total time: " << duration_cast<duration<float>>(now - start).count() << std::endl;
	ComputeShader.SetFloat("time", time);
	ComputeShader.SetFloat("seed", rand() % 100 + 1); // random seed from 1 to 100
	ComputeShader.SetVec2("spawnCenter", position);

	// Invoke Compute Shader and wait for all memory access to SSBO to safely finish
	ComputeShader.Bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);
	glDispatchCompute((this->Particles.size() / 128) + 1, 1, 1);	// group size: 128
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	ComputeShader.UnBind();

	RenderShader.SetMat4("projection", ae.mCameraManager->GetProjectionMatrix());
	RenderShader.SetVec2("cameraPos", ae.mCameraManager->getPosition());

	// Render the results
	RenderShader.Bind();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_POINTS, 0, 1, this->Particles.size());
	glBindVertexArray(0);

	lastFrameTime = now;
}



void ParticleEffect::Destory()
{
	glDeleteBuffers(1, &SSBO);
	glDeleteVertexArrays(1, &VAO);
}



void ParticleEffect::Print()
{
	std::stringstream ss;
	ss << "Compute Shader Capabilities:" << std::endl;
	ss << "GL_MAX_COMPUTE_WORK_GROUP_COUNT:" << std::endl;
	for (int i : {0, 1, 2}) {
		int tmp = 0;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, i, &tmp);
		ss << tmp << std::endl;
	}

	ss << "GL_MAX_COMPUTE_WORK_GROUP_SIZE:" << std::endl;
	for (int i : {0, 1, 2}) {
		int tmp = 0;
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &tmp);
		ss << tmp << std::endl;
	}

	ss << "Number of Particles: " << Particles.size() << std::endl;

	std::cout << ss.str() << std::endl;
}



float gen_random(float min, float max) {
	static std::random_device rd;
	static std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}






Particle::Particle(glm::vec2 position, glm::vec2 velocity, float scale, float time)
	:position(position),
	velocity(velocity),
	scale(scale),
	duration(time)
{}


glm::vec2 randomPointInCircle(glm::vec2 center, float radius)
{
	float r = radius * sqrt(gen_random(0, 1));
	float theta = gen_random(0, 1) * 2 * 3.1415f;

	float x = center[0] + r * cosf(theta);
	float y = center[1] + r * sinf(theta);

	return glm::vec2(x, y);
}

glm::vec2 randomPointInSquare(glm::vec2 center, float length)
{
	float posX = gen_random(center[0] - length, center[0] + length);
	float posY = gen_random(center[1] - length, center[1] + length);
	return glm::vec2(posX, posY);
}



glm::vec2 GenRandomCircSectorDir(float angle1, float angle2)
{
	float angle = gen_random(angle1, angle2);	// random angle from 0 to 2 PI
	return glm::vec2(cosf(angle), sinf(angle));
}


glm::vec2 GenRandomCircDir()
{
	return GenRandomCircSectorDir(0.0f, 2.0f * 3.1415f);
}

float CalVecAngle(glm::vec2 vec)
{
	float angle = atan2f(vec[1], vec[0]);;
	//if (angle < 0) { angle += 2 * 3.1415f; }
	return angle;
}



ParticleEffect::ParticleEffect(SpawnConfig spawnConfig, MoveConfig moveConfig, ParticleConfig paConfig)
	:Particles(), ComputeShader("Atom/res/shaders/ParticleEffect.shader"),
	RenderShader("Atom/res/shaders/RenderParticle.shader")

{
	for (int i = 0; i < paConfig.numOfParticles; ++i) {
		glm::vec2 pos(0.0f);
		glm::vec2 velocity(0.0f);

		if (spawnConfig.mode == SQUARE)
		{
			spawnCenter = spawnConfig.areaCenter;
			pos = randomPointInSquare(spawnConfig.areaCenter, spawnConfig.length);
		}
		else if (spawnConfig.mode == CIRCLE)
			pos = randomPointInCircle(spawnConfig.areaCenter, spawnConfig.length);

		if (moveConfig.mode == LINEAR)
			velocity = moveConfig.direction * moveConfig.magnitude;
		else if (moveConfig.mode == CIRCULAR)
			velocity = GenRandomCircDir() * moveConfig.magnitude;

		// TODO
		// this mode has some bugs
		/*
		else if (moveConfig.mode == CIRCULAR_SECTOR)
		{
			float angle = CalVecAngle(moveConfig.direction);

			float minAngle = angle - moveConfig.angle / 2.0f;
			float maxAngle = angle + moveConfig.angle / 2.0f;
			velocity = GenRandomCircSectorDir(minAngle, maxAngle) * moveConfig.magnitude;
		}
		*/

		float time = gen_random(paConfig.time[0], paConfig.time[1]);
		Particles.push_back(Particle(pos, velocity, paConfig.scale, time));
	}
}

