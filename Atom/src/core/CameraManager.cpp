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
	ae.addEventListener(EventID::E_ENTITY_DIE, [this](Event& e) {this->onEvent(e); });
}

void CameraManager::update()
{
	if (shakeTime > 0)
	{
		shakeTime -= ae.dt;
	}
}

void CameraManager::onEvent(Event& e)
{
	EntityID entity = e.getParam<EntityID>(EventID::P_ENTITY_DIE);
	
	if (ae.hasComponent<ControllerComponent>(entity))
	{
		shakeTime = maxShakeTime;
	}

}


glm::vec2 CameraManager::getPosition()
{
	if (shakeTime > 0)
	{
		float r = ((double)rand() / RAND_MAX) - 0.5;
		return camera.position + glm::vec2(r * shakeness * shakeTime);
	}
	else
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