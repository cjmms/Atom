#include "Pch.hpp"
#include "ChaseSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

void ChaseSystem::init()
{

}

void ChaseSystem::update()
{
	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<ChasePlayerComponent>(entity))
		{
			auto& chasePlayer = ae.getComponent<ChasePlayerComponent>(entity);
			auto& sourceTransform = ae.getComponent<TransformComponent>(entity);
			auto& targetTransform = ae.getComponent<TransformComponent>(chasePlayer.target);
			glm::vec3 direction = targetTransform.position - sourceTransform.position;
			
			if (glm::length(direction) > 5.0)
				continue;
			
			glm::vec3 normDirection = glm::normalize(direction);
			auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			body.velocityX = normDirection.x * chasePlayer.speed;
			body.velocityY = normDirection.y * chasePlayer.speed;

		}
	}
}

void ChaseSystem::onEvent(Event& e)
{

}
