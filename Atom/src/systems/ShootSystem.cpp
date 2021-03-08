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
			if(shoot.timer > 0)	//cooling down
				shoot.timer -= frameTime;
			else if(shoot.isShooting)
			{
				shoot.timer += shoot.shootInterval;
				auto& transform = ae.getComponent<TransformComponent>(entity);
				float offset = 0.1;	//may need to store in shoot component
				float bulletX = transform.position.x + cos(shoot.direction) * offset;
				float bulletY = transform.position.y + sin(shoot.direction) * offset;
				EntityID bullet = ae.createEntity();

				//todo ser/deser of bullet obj
				ae.addComponent(bullet, RectangleComponent{
					glm::vec3{1.0f,1.0f,1.0f},
					false
					});

				ae.addComponent(bullet, ShapeComponent{ShapeComponent::AABB});

				auto body = PhysicsBodyComponent(0.01f, false, true);
				float speed = 1;
				body.velocityX = cos(shoot.direction) * speed;
				body.velocityY = sin(shoot.direction) * speed;
				ae.addComponent(bullet, body);

				ae.addComponent(bullet, TransformComponent{
					glm::vec3{bulletX,bulletY, 0.0f}, // position
					glm::vec3{0.0f,0.0f,0.0f}, // rotation
					glm::vec3{0.01f,0.01f,1.0f},  // scale 
					glm::mat4(1.0f)
					});

				ae.addComponent(bullet, DamageComponent{50});

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
