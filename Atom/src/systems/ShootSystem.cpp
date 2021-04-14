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

extern string sfxJump;
extern string sfxLand;
extern string sfxBullet;

extern float sfxVolumedB;

void playBulletSound() {
	ae.play(sfxBullet, ChannelGroupTypes::C_SFX, sfxVolumedB);
}

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

				auto& autoShoot = ae.getComponent<AutoShootComponent>(entity);
				auto& sourceTransform = ae.getComponent<TransformComponent>(entity);

				EntityID target;
				float shortestDist = 1.5;
				glm::vec3 targetDirection;
				//auto& targetTransform = ae.getComponent<TransformComponent>(target);
				
				shoot.isShooting = false;
				//loop through player characters and find nearest one
				for (auto itr = targetPlayers.begin(); itr != targetPlayers.end(); ++itr)
				{
					//auto& targetTransform = ae.getComponent<TransformComponent>(autoShoot.target);
					auto& targetTransform = ae.getComponent<TransformComponent>(*itr);
					glm::vec3 direction = targetTransform.position - sourceTransform.position;

					float dist = glm::length(direction);

					if (dist < 1.5 && ae.getComponent<HealthComponent>(*itr).health > 0)
					{
						shoot.isShooting = true;
						if (dist < shortestDist)
						{
							shortestDist = dist;
							target = *itr;
							targetDirection = direction;
						}
					}

				}

				if (shoot.isShooting)
				{
					glm::vec3 normDirection = glm::normalize(targetDirection);
					shoot.direction = atan2(normDirection.y, normDirection.x);
				}
				
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

					float offsetX = fabs(transform.scale.x) * 0.5;	//may need to store in shoot component
					float offsetY = fabs(transform.scale.y) * 0.5;	//may need to store in shoot component
					float bulletX = transform.position.x + cos(shootDirection) * offsetX;
					float bulletY = transform.position.y + sin(shootDirection) * offsetY;
					EntityID bullet = ae.createEntity();

					ae.addComponent(bullet, BulletComponent());
					ae.addComponent(bullet, ParticleComponent());
					//todo ser/deser of bullet obj
					ae.addComponent(bullet, RectangleComponent{
						glm::vec3{1.0f,1.0f,1.0f},
						false,
						shoot.bulletTexturePath
						});

					ae.addComponent(bullet, ShapeComponent{ShapeType::AABB});

					auto body = PhysicsBodyComponent(0.01f, false, true, false);
					float speed = shoot.bulletSpeed;
					body.velocityX = cos(shootDirection) * speed;
					body.velocityY = sin(shootDirection) * speed;
					body.isTrigger = true;
					ae.addComponent(bullet, body);

					ae.addComponent(bullet, TransformComponent{
						glm::vec3{bulletX,bulletY, 0.0f}, // position
						glm::vec3{0.0f,0.0f,0.0f}, // rotation
						glm::vec3{shoot.bulletScale,shoot.bulletScale,1.0f},  // scale 
						glm::mat4(1.0f)
						});

					string tag = "";
					if (ae.hasComponent<TagComponent>(entity))
					{
						 tag = ae.getComponent<TagComponent>(entity).tag;
					}

					ae.addComponent(bullet, DamageComponent{30, tag});

					ae.addComponent(bullet, SelfDestroyComponent(5));
					


					////to send to Entity Manager for handling destroy event
					//Event e(EventID::E_SELF_DESTROY);
					//e.setParam<EntityID>(EventID::P_SELF_DESTROY_ENTITYID, bullet);
					//ae.mEventManager->sendTimedEvent(e, 3000);
				}
				playBulletSound();

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
	if (e.getType() == EventID::E_AUDIO_PLAY) {
		auto audioloc = e.getParam<string>(EventID::P_AUDIO_PLAY_AUDIOLOC);
		auto chgroup = e.getParam<ChannelGroupTypes>(EventID::P_AUDIO_PLAY_CHANNELGROUP);
		auto volumedb = e.getParam<float>(EventID::P_AUDIO_PLAY_VOLUMEDB);
		ae.play(audioloc, chgroup, std::clamp(volumedb, 0.0f, 1.0f));
	}
}
