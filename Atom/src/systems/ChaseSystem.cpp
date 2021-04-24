/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		ChaseSystem.cpp
* @author	Gerald Lee
* @brief	Enemy Logic for Chasing
* @date		2021-03-11
*/

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
			//auto& targetTransform = ae.getComponent<TransformComponent>(chasePlayer.target);

			//todo temp get player target
			auto& targetPlayers = ae.mSystemManager->getSystem<ControllerSystem>()->mEntities;
			if (targetPlayers.size() == 0)
				return;

			EntityID target;
			float shortestDist = 1.5;
			glm::vec3 targetDirection(0, 0, 0);
			for (auto itr = targetPlayers.begin(); itr != targetPlayers.end(); ++itr)
			{
				//auto& targetTransform = ae.getComponent<TransformComponent>(autoShoot.target);
				auto& targetTransform = ae.getComponent<TransformComponent>(*itr);
				glm::vec3 direction = targetTransform.position - sourceTransform.position;

				float dist = glm::length(direction);

				if (dist < 1.5 && ae.getComponent<HealthComponent>(*itr).health > 0)
				{
					if (dist < shortestDist)
					{
						shortestDist = dist;
						target = *itr;
						targetDirection = direction;
					}
				}
			}
			//EntityID target = *targetPlayers.begin();
			//auto& targetTransform = ae.getComponent<TransformComponent>(target);
			//
			//glm::vec3 direction = targetTransform.position - sourceTransform.position;
			//
			//if (glm::length(direction) > 3.0)
			//	continue;
			
			glm::vec3 normDirection = glm::normalize(targetDirection);
			auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			body.velocityX = normDirection.x * chasePlayer.speed;
			//body.velocityY = normDirection.y * chasePlayer.speed;

		}
	}
}

void ChaseSystem::onEvent(Event& e)
{

}
