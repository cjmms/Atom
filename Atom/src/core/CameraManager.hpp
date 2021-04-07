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
	void update() {};
	void onEvent(Event &e) {};
	void reset() {};

	glm::vec2 getPosition();
	void setPosition(glm::vec2 pos);


	glm::mat4 GetProjectionMatrix();

	Camera camera;
};

