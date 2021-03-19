#include "Pch.hpp"
#include "ShootSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/PhysicsBodyComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/ShootComponent.hpp"
#include "components/DamageComponent.hpp"

extern AtomEngine ae;

void ShootSystem::init()
{
}

void ShootSystem::update()
{
	float frameTime = ae.dt;

	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<ShootComponent>(entity))
		{
			auto& shoot = ae.getComponent<ShootComponent>(entity);

			//always enable shoot
			//todo can write another system for AutoShootComponent for smarter enemy shooting
			if (ae.hasComponent<AutoShootComponent>(entity))
			{

				//todo temp get player target
				auto& targetPlayers = ae.mSystemManager->getSystem<ControllerSystem>()->mEntities;
				if (targetPlayers.size() == 0)
					return;
				EntityID target = *targetPlayers.begin();
				//auto& targetTransform = ae.getComponent<TransformComponent>(target);


				auto& autoShoot = ae.getComponent<AutoShootComponent>(entity);
				shoot.isShooting = true;
				auto& sourceTransform = ae.getComponent<TransformComponent>(entity);

				//auto& targetTransform = ae.getComponent<TransformComponent>(autoShoot.target);
				auto& targetTransform = ae.getComponent<TransformComponent>(target);
				glm::vec3 direction = targetTransform.position - sourceTransform.position;

				if (glm::length(direction) > 3.0)
				{
					shoot.isShooting = false;
					continue;
				}


				glm::vec3 normDirection = glm::normalize(direction);
				shoot.direction = atan2(normDirection.y, normDirection.x);

			}

			if(shoot.timer > 0)	//cooling down
				shoot.timer -= frameTime;
			else if(shoot.isShooting)
			{
				shoot.timer += shoot.shootInterval;
				auto& transform = ae.getComponent<TransformComponent>(entity);

				for (int i = 0; i < shoot.bulletPerShoot; i++)
				{
					float shootDirection = shoot.direction;

					//		+   (idx from up/down * angle * odd->down, even->up)
					shootDirection += (i + 1) / 2 * PI / 12 * (i % 2 == 1 ? -1 : 1);

					float offsetX = transform.scale.x * 1.2;	//may need to store in shoot component
					float offsetY = transform.scale.y * 1.2;	//may need to store in shoot component
					float bulletX = transform.position.x + cos(shootDirection) * offsetX;
					float bulletY = transform.position.y + sin(shootDirection) * offsetY;
					EntityID bullet = ae.createEntity();

					ae.addComponent(bullet, BulletComponent());

					//todo ser/deser of bullet obj
					ae.addComponent(bullet, RectangleComponent{
						glm::vec3{1.0f,1.0f,1.0f},
						false
						});

					ae.addComponent(bullet, ShapeComponent{ShapeType::AABB});

					auto body = PhysicsBodyComponent(0.01f, false, true, false);
					float speed = 1.5;	//todo store bullet speed
					body.velocityX = cos(shootDirection) * speed;
					body.velocityY = sin(shootDirection) * speed;
					ae.addComponent(bullet, body);

					ae.addComponent(bullet, TransformComponent{
						glm::vec3{bulletX,bulletY, 0.0f}, // position
						glm::vec3{0.0f,0.0f,0.0f}, // rotation
						glm::vec3{0.01f,0.01f,1.0f},  // scale 
						glm::mat4(1.0f)
						});

					ae.addComponent(bullet, DamageComponent{50, entity});
				}

			}
			else
			{
				//ready for shoot && not shooting, do nothing
			}
		}

	}
}

void ShootSystem::onEvent(Event& e)
{
	
}
