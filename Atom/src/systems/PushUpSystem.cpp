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
	
}

void PushUpSystem::update()
{
	for (auto entity : ae.mSystemManager->getSystem<ControllerSystem>()->mEntities)
	{
		if (ae.hasComponent<ControllerComponent>(entity) && ae.getComponent<CharacteristicComponent>(entity).isBig)
		{
			BigChar = entity;
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

	auto& body = ae.getComponent<PhysicsBodyComponent>(BigChar);

	if (PushUpPlatforms.size() != 0)
	{
		for (auto& platform : PushUpPlatforms)
		{
			auto pushUp = ae.getComponent<PushUpComponent>(platform);
			auto pushUpBody = ae.getComponent<PhysicsBodyComponent>(platform);

			if (body.prevPositionX >= (pushUpBody.prevPositionX - pushUp.Scale * SCALE) && body.prevPositionX <= (pushUpBody.prevPositionX + pushUp.Scale * SCALE) && body.prevPositionY > pushUpBody.prevPositionY)
			{
				body.totalForceX = pushUp.ForceX / ((body.prevPositionY - pushUpBody.prevPositionY) * (body.prevPositionY - pushUpBody.prevPositionY) * 100 * 100);
				body.totalForceY = pushUp.ForceY / ((body.prevPositionY - pushUpBody.prevPositionY) * (body.prevPositionY - pushUpBody.prevPositionY) * 100 * 100);
			}
		}
	}
}

void PushUpSystem::onEvent(Event& e)
{

}