#include "Pch.hpp"
#include "HealthSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/HealthComponent.hpp"

extern AtomEngine ae;

void HealthSystem::init()
{
	//ae.addEventListener(EventID::E_COLLISION, [this](Event& e) {this->onEvent(e); });
}

void HealthSystem::update()
{
	//std::vector<EntityID> destroyList;
	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<HealthComponent>(entity))
		{
			auto& health = ae.getComponent<HealthComponent>(entity);
			//todo temp ae.getComponent<ControllerComponent>(entity), need restart game logic here
			if (health.health <= 0 && !ae.hasComponent<ControllerComponent>(entity))
			{
				//destroyList.push_back(entity);
				ae.EnqueueDestroyEntity(entity);
			}
		}
	}

	//for (int i = destroyList.size() - 1; i >= 0; i--)
	//{
	//	ae.destroyEntity(destroyList[i]);
	//}
}

void HealthSystem::onEvent(Event& e)
{
}
