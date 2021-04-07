#include "Pch.hpp"
#include "CameraManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/AtomEngine.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;


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





glm::mat4 CameraManager::GetProjectionMatrix()
{
	float width = ae.mGraphicsManager->GetWindowWidth();
	float height = ae.mGraphicsManager->GetWindowHeight();
	return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
}