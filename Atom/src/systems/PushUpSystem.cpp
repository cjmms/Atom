/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		PushUpSystem.cpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Contains logic for entities that constantly apply a constant force
* @date		2021-07-07
*/

#include "Pch.hpp"
#include "PushUpSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

#define SCALE 0.125f

void PushUpSystem::init()
{
	scale = 0.125f;
}

void PushUpSystem::update()
{
	scale = 50.0f / ae.mGraphicsManager->GetLevelWidth();

	if (ae.mSystemManager->getSystem<ControllerSystem>()->mEntities.size() == 0)
		BigChar = -1;
	else
	{
		for (auto entity : ae.mSystemManager->getSystem<ControllerSystem>()->mEntities)
		{
			if (ae.hasComponent<ControllerComponent>(entity) && ae.getComponent<CharacteristicComponent>(entity).isBig)
			{
				BigChar = entity;
			}
		}
	}
	

	std::vector<EntityID> PushUpPlatforms;
	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<PushUpComponent>(entity))
		{
			PushUpPlatforms.push_back(entity);
		}
	}

	PhysicsBodyComponent* body;
	
	if(BigChar != -1)
		body = &ae.getComponent<PhysicsBodyComponent>(BigChar);

	if (PushUpPlatforms.size() != 0)
	{
		for (auto& platform : PushUpPlatforms)
		{
			auto pushUp = ae.getComponent<PushUpComponent>(platform);
			auto pushUpBody = ae.getComponent<PhysicsBodyComponent>(platform);

			if (body->prevPositionX >= (pushUpBody.prevPositionX - pushUp.Scale * scale) && body->prevPositionX <= (pushUpBody.prevPositionX + pushUp.Scale * scale) && body->prevPositionY > pushUpBody.prevPositionY)
			{
				body->totalForceX = pushUp.ForceX / ((body->prevPositionY - pushUpBody.prevPositionY) * (body->prevPositionY - pushUpBody.prevPositionY) * 100 * 100);
				body->totalForceY = pushUp.ForceY / ((body->prevPositionY - pushUpBody.prevPositionY) * (body->prevPositionY - pushUpBody.prevPositionY) * 100 * 100);
			}
		}
	}
}

void PushUpSystem::onEvent(Event& e)
{

}