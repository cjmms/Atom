#include "Pch.hpp"
#include "MoveToSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/AllComponents.hpp"

#define CONVERSION_FACTOR 8.0f

extern AtomEngine ae;


void MoveToSystem::init()
{
	ae.addEventListener(EventID::E_TRIGGER, [this](Event& e) {this->onEvent(e); });

	conversion_factor = 8.0f;
}

void MoveToSystem::update()
{
	conversion_factor = ae.mGraphicsManager->GetLevelWidth() / 100.0f;

	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<MoveToComponent>(entity))
		{
			auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			//auto& tag = ae.getComponent<TagComponent>(entity);
			auto& moveTo = ae.getComponent<MoveToComponent>(entity);

			body.velocityX = 0;
			body.velocityY = 0;
			
			//Check if associated trigger is triggered
			for (auto str : tags)
			{
				//if tags match
				if (str == moveTo.tag)
				{
					//Moving in X axis
					if (moveTo.GridX >= 0)
					{
						body.velocityX = moveTo.velocityX;
						moveTo.GridX = moveTo.GridX - (abs(moveTo.velocityX) * ae.dt * conversion_factor);
					}
					else
					{
						body.velocityX = 0;
					}

					//Moving in Y axis
					if (moveTo.GridY >= 0)
					{
						body.velocityY = moveTo.velocityY;
						moveTo.GridY = moveTo.GridY - (abs(moveTo.velocityY) * ae.dt * conversion_factor);
					}
					else
					{
						body.velocityY = 0;
					}
				}
				else
				{
					body.velocityX = 0;
					body.velocityY = 0;
				}
			}
		}

	}

	
}

void MoveToSystem::onEvent(Event& e)
{
	if (e.getType() == EventID::E_TRIGGER)
	{
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

		if (skillComponent.skillType == SkillType::Trigger)
		{
			auto& tagComponent = ae.getComponent<TagComponent>(skillEntity);
			tags.push_back(tagComponent.tag);
		}
	}
}