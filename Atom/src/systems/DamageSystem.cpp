#include "Pch.hpp"
#include "DamageSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/DamageComponent.hpp"

extern AtomEngine ae;

void DamageSystem::init()
{
	ae.addEventListener(EventID::E_COLLISION, [this](Event& e) {this->onEvent(e); });
}

void DamageSystem::update()
{
	std::vector<EntityID> destroyList;
	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<DamageComponent>(entity))
		{
			auto& damage = ae.getComponent<DamageComponent>(entity);
			if (damage.destroy)
			{
				destroyList.push_back(entity);
			}
		}
	}

	for (int i = destroyList.size() - 1; i >= 0; i--)
	{
		ae.destroyEntity(destroyList[i]);
	}
}

void DamageSystem::onEvent(Event& e)
{
	if (e.getType() != EventID::E_COLLISION)
		return;

	EntityID e1 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID1);
	EntityID e2 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID2);

	EntityID bullet = -1, target = -1;

	if (ae.hasComponent<DamageComponent>(e1))
	{
		bullet = e1;
		target = e2;
	}
	if (ae.hasComponent<DamageComponent>(e2))
	{
		if (bullet != -1)
		{
			//both bullet
			ae.getComponent<DamageComponent>(e1).destroy = true;
			ae.getComponent<DamageComponent>(e2).destroy = true;
			return;
		}
		else
		{
			bullet = e2;
			target = e1;
		}
	}

	if (bullet == -1)
		return;

	auto& damage = ae.getComponent<DamageComponent>(bullet);
	
	////ignore self-damage
	////todo may need to ignore collision also
	//if (damage.ownerID == target)
	//	return;
	
	if (ae.hasComponent<HealthComponent>(target))
	{
		auto& health = ae.getComponent<HealthComponent>(target);
		health.health -= damage.damage;
	}

	//handle destroy in another loop
	if (ae.hasComponent<BulletComponent>(bullet))
		damage.destroy = true;

}
