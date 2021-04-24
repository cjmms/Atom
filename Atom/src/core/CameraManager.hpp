/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		CameraManager.hpp
* @author	Gerald Lee
* @brief	Controls camera movement and effects
* @date		2021-03-14
*/

#pragma once
#include "Pch.hpp"
#include "core/Types.hpp"
#include "core/Event.hpp"
#include "utils/Log.hpp"

class Camera
{
public:

	glm::vec2 position;
};


class CameraManager
{
public:
	void init();
	void update();
	void onEvent(Event &e);
	void reset() {};

	glm::vec2 getPosition();
	void setPosition(glm::vec2 pos);


	glm::mat4 GetProjectionMatrix();

	Camera camera;

	float maxShakeTime = 0.8f;
	float shakeTime = 0.0f;
	float shakeness = 0.05f;
};

