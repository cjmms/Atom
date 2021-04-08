#include "Pch.hpp"
#include "DamageSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/DamageComponent.hpp"

extern AtomEngine ae;

void DamageSystem::init()
{
	ae.addEventListener(EventID::E_TRIGGER, [this](Event& e) {this->onEvent(e); });
}

void DamageSystem::update()
{
	//std::vector<EntityID> destroyList;
	//for (auto& entity : mEntities)
	//{
	//	if (ae.hasComponent<DamageComponent>(entity))
	//	{
	//		auto& damage = ae.getComponent<DamageComponent>(entity);
	//		if (damage.destroy)
	//		{
	//			destroyList.push_back(entity);
	//		}
	//	}
	//}
	//
	//for (int i = destroyList.size() - 1; i >= 0; i--)
	//{
	//	ae.destroyEntity(destroyList[i]);
	//}
}

void DamageSystem::onEvent(Event& e)
{
	if (e.getType() != EventID::E_TRIGGER)
		return;

	EntityID e1 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID1);
	EntityID e2 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID2);

	EntityID damageSource = -1, target = -1;

	if (ae.hasComponent<DamageComponent>(e1))
	{
		damageSource = e1;
		target = e2;
	}
	if (ae.hasComponent<DamageComponent>(e2))
	{
		if (damageSource != -1)
		{
			//both bullet
			//ae.EnqueueDestroyEntity(e1);
			//ae.EnqueueDestroyEntity(e2);
			//ae.getComponent<DamageComponent>(e1).destroy = true;
			//ae.getComponent<DamageComponent>(e2).destroy = true;
			return;
		}
		else
		{
			damageSource = e2;
			target = e1;
		}
	}

	if (damageSource == -1)
		return;

	auto& damage = ae.getComponent<DamageComponent>(damageSource);
	
	//avoid team kill
	if (ae.hasComponent<TagComponent>(target))
	{
		string targetTag = ae.getComponent<TagComponent>(target).tag;
		if (targetTag == damage.tag)
			return;
	}
	
	//avoid bullet hitting non-collider
	if (ae.hasComponent<PhysicsBodyComponent>(target))
	{
		PhysicsBodyComponent& body = ae.getComponent<PhysicsBodyComponent>(target);
		if (body.isTrigger)
			return;
	}
	else
		return;

	//God Mode Check
	if (ae.hasComponent<CharacteristicComponent>(target))
	{
		auto& character = ae.getComponent<CharacteristicComponent>(target);
		if (character.inGodMode || character.inSuperGodMode)
		{
			//handle destroy in another loop
			if (ae.hasComponent<BulletComponent>(damageSource))
			{
				ae.EnqueueDestroyEntity(damageSource);
				//damage.destroy = true;
			}
			return;
		}
	}

	if (ae.hasComponent<HealthComponent>(target))
	{
		auto& health = ae.getComponent<HealthComponent>(target);
		health.health -= damage.damage;
	}

	//handle destroy in another loop
	if (ae.hasComponent<BulletComponent>(damageSource))
	{
		ae.EnqueueDestroyEntity(damageSource);
		//damage.destroy = true;
	}

}
