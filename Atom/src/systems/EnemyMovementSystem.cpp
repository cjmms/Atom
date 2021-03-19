#include "Pch.hpp"
#include "EnemyMovementSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

void EnemyMovementSystem::init()
{

}

void EnemyMovementSystem::update()
{
	for (auto& entity : mEntities)
	{
		auto& movement = ae.getComponent<HorizontalMovementComponent>(entity);
		auto& transform = ae.getComponent<TransformComponent>(entity);
		auto& body = ae.getComponent<PhysicsBodyComponent>(entity);

		//float time = ae.mChrononManager->getUptime();

		movement.currentTime += ae.dt;
		if (movement.currentTime > movement.tripTime)
		{
			movement.currentTime -= movement.tripTime;
			movement.oppositeDirection = !movement.oppositeDirection;
		}

		body.velocityX = movement.velocity * (movement.oppositeDirection ? -1 : 1);
	}
}

void EnemyMovementSystem::onEvent(Event& e)
{

}