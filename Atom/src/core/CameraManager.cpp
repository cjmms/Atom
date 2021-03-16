#include "Pch.hpp"
#include "CameraManager.hpp"

void CameraManager::init()
{
	camera.position = glm::vec2(0.0f);
}


glm::vec2 CameraManager::getPosition()
{
	return camera.position;
}


void CameraManager::setPosition(glm::vec2 pos)
{
	camera.position = pos;
}