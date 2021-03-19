#include "Pch.hpp"
#include "SkillSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

//Temp

extern AtomEngine ae;

void SkillSystem::init()
{
	ae.addEventListener(EventID::E_TRIGGER, [this](Event& e) {this->onEvent(e); });
}

void SkillSystem::update()
{
	std::vector<EntityID> destroyList;
	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<SkillBoosterComponent>(entity))
		{
			auto& damage = ae.getComponent<SkillBoosterComponent>(entity);
			if (damage.destroy)
				destroyList.push_back(entity);
		}
	}

	for (int i = destroyList.size() - 1; i >= 0; i--)
	{
		ae.destroyEntity(destroyList[i]);
	}
}

void SkillSystem::onEvent(Event& e)
{
	if (e.getType() == EventID::E_TRIGGER) {
		EntityID e1 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID1);
		EntityID e2 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID2);

		EntityID skillEntity = -1;
		EntityID playerEntity = -1;
		if (ae.hasComponent<SkillBoosterComponent>(e1) && ae.hasComponent<CharacteristicComponent>(e2))
		{
			skillEntity = e1;
			playerEntity = e2;

		}
		else if (ae.hasComponent<CharacteristicComponent>(e1) && ae.hasComponent<SkillBoosterComponent>(e2))
		{
			playerEntity = e1;
			skillEntity = e2;
		}
		else
		{
			return;
		}

		auto& skillComponent = ae.getComponent<SkillBoosterComponent>(skillEntity);

		switch (skillComponent.skillType)
		{
		case DoubleJump:
		{
			auto& characterComponent = ae.getComponent<CharacteristicComponent>(playerEntity);
			characterComponent.canDoubleJump.isEnabled = true;
			break;
		}
		case WallJump:
		{
			auto& characterComponent = ae.getComponent<CharacteristicComponent>(playerEntity);
			characterComponent.canWallJump.isEnabled = true;
			break;
		}
		case BulletCount:
		{
			auto& shootComponent = ae.getComponent<ShootComponent>(playerEntity);
			shootComponent.bulletPerShoot += 2;
			break;
		}
		case BulletSpeed:
		{
			auto& shootComponent = ae.getComponent<ShootComponent>(playerEntity);
			shootComponent.shootInterval *= 0.8;
			break;
		}
		default:
			ATOM_ERROR("Skill : Missing new skill");
			break;
		}

		skillComponent.destroy = true;
	}
}
