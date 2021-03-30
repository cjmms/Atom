#include "Pch.hpp"
#include "AutoMovementSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

void AutoMovementSystem::init()
{

}

void AutoMovementSystem::update()
{
	for (auto& entity : mEntities)
	{
		auto& movement = ae.getComponent<AutoMovementComponent>(entity);
		auto& transform = ae.getComponent<TransformComponent>(entity);
		auto& body = ae.getComponent<PhysicsBodyComponent>(entity);

		//float time = ae.mChrononManager->getUptime();

		movement.currentTime += ae.dt;
		if (movement.currentTime > movement.tripTime)
		{
			movement.currentTime -= movement.tripTime;
			movement.oppositeDirection = !movement.oppositeDirection;
		}

		body.velocityX = movement.velocityX * (movement.oppositeDirection ? -1 : 1);
		if(!body.gravity)
			body.velocityY = movement.velocityY * (movement.oppositeDirection ? -1 : 1);
	}
}

void AutoMovementSystem::onEvent(Event& e)
{

}