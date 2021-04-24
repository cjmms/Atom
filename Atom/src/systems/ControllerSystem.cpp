/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		ControllerSystem.cpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Contains logic for character reaction to controls and any other logic regarding for Player Character
* @date		date 2021-02-03
*/

#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "RectangleRenderSystem.hpp"
#include "utils/Log.hpp"
#include "components/ControllerComponent.hpp"
#include "components/PhysicsBodyComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/CharacteristicComponent.hpp"
#include "components/ShootComponent.hpp"

//Temp

extern AtomEngine ae;

extern ChannelID sfxChannelID;

extern string sfxJump;
extern string sfxLand;
extern string sfxBullet;


float lerp(float a, float b, float t, float lo, float hi) {
	if (lo == hi) {
		return a;
	}
	t = (t - lo) / (hi - lo);
	float res = a * (1 - t) + b * (t);
	return res;
}

float camera_fade_time = 0.3f;
glm::vec2 target_position;
glm::vec2 current_position;


extern string sfxJump;
extern string sfxLand;
extern float sfxVolumedB;

void ControllerSystem::init()
{
	ae.addEventListener(EventID::E_AUDIO_PLAY, [this](Event& e) {this->onEvent(e); });
	ae.addEventListener(EventID::E_COLLISION, [this](Event& e) {this->onEvent(e);});

	shouldFollow = true;
}



// current pos -> target pos - 1s

void ControllerSystem::update()
{
	EntityID activeEntity = -1;
	EntityID inactiveEntity = -1;
	
	for (auto& entity : mEntities) 
	{
		if (ae.hasComponent<ControllerComponent>(entity)) 
		{
			auto& controller = ae.getComponent<ControllerComponent>(entity);
			
			if(controller.isActive)
				activeEntity = entity;
			else
				inactiveEntity = entity;
		}

	}	

	if (activeEntity == -1) {
		return;
	}

	auto& body1 = ae.getComponent<PhysicsBodyComponent>(activeEntity);
	auto& character1 = ae.getComponent<CharacteristicComponent>(activeEntity);
	auto& controller = ae.getComponent<ControllerComponent>(activeEntity);
	auto& transformComponent = ae.getComponent<TransformComponent>(activeEntity);
	auto& health1 = ae.getComponent<HealthComponent>(activeEntity);
	
	auto& body2 = ae.getComponent<PhysicsBodyComponent>(inactiveEntity);
	auto& character2 = ae.getComponent<CharacteristicComponent>(inactiveEntity);
	auto& controller2 = ae.getComponent<ControllerComponent>(inactiveEntity);
	auto& health2 = ae.getComponent<HealthComponent>(inactiveEntity);

	//restart game
	if (health1.health <= 0 && health2.health <= 0)
	{
		ae.mLevelManager->restartCurrentLevel();
		return;
	}

	//cannot control character of zero health
	if (health1.health <= 0)
	{
		//active char die, switch to another char
		ae.getComponent<ShootComponent>(activeEntity).isShooting = false;
		controller.isActive = false;
		controller2.isActive = true;
		return;
	}
	

	glm::vec2 target_position = glm::vec2{ transformComponent.position.x,transformComponent.position.y };

	//Setting Camera - Follow active entity
	if (shouldFollow)
	{

		float x = lerp(ae.mCameraManager->getPosition().x, target_position.x, ae.dt, 0.0f, camera_fade_time);
		float y = lerp(ae.mCameraManager->getPosition().y, target_position.y, ae.dt, 0.0f, camera_fade_time);
		ae.mCameraManager->setPosition(glm::vec2{ x,y });
		playerPosition = glm::vec2{ x, y };
	}



	{//Mouse
		{
			auto& shoot = ae.getComponent<ShootComponent>(activeEntity);
			if (ae.mInputManager->isKeyPressed(VK_LBUTTON))
			{
				//direction
				std::pair<double, double> curPosition = ae.mInputManager->getCursorPos();
				//ATOM_INFO("Cursor Xposition : {}, Yposition : {}", curPosition.first, curPosition.second);
				//ATOM_INFO("Body Xposition : {}, Yposition : {}", (body.prevPositionX + 1) / 2 * width, (1 - body.prevPositionY) / 2 * height);

				int width = ae.mGraphicsManager->GetWindowWidth();
				int height = ae.mGraphicsManager->GetWindowHeight();;

				//old way of getting direction when camera is fixed
				//float x = curPosition.first - (body.prevPositionX + 1) / 2 * width;
				//float y = (1 - body.prevPositionY) / 2 * height - curPosition.second;

				//assume main char is always at center
				float x = curPosition.first - width / 2;
				float y = height / 2 - curPosition.second;
				//ATOM_INFO("Width: {}, Height: {}", width, height);

				shoot.direction = atan2(y, x);

				//ATOM_INFO("direction: {}", body.direction);

				shoot.isShooting = true;
				//playBulletSound();
			}
			else
			{
				shoot.isShooting = false;
			}
		}

		if (ae.mInputManager->isKeyPressed(VK_RBUTTON))
		{
			std::pair<double, double> dPosition = ae.mInputManager->getCursorPosChange();
			//ATOM_INFO("Left Mouse Button is pressed, Change in Xposition : {}, Change in Yposition : {}",dPosition.first, dPosition.second);

			glm::vec2 cameraPos = ae.mCameraManager->getPosition();

			cameraPos.x -= dPosition.first / 200;
			cameraPos.y += dPosition.second / 200;

			//ae.mSystemManager->getSystem<RectangleRenderSystem>()->setCameraPos(cameraPos);
			ae.mCameraManager->setPosition(cameraPos);

			//ATOM_INFO("Camera Position x : {} , y : {}", cameraPos.x, cameraPos.y);
			shouldFollow = false;
		}
		else
		{
			shouldFollow = true;
		}
	}



	{//Triggered

		if (ae.mInputManager->isKeyTriggered(controller.GOD_MODE))
		{
			if(character1.inGodMode)
			{
				character1.inGodMode = false;
			}
			else
			{
				character1.inGodMode = true;
			}
		}
		
		if (ae.mInputManager->isKeyTriggered(controller.SUPER_GOD_MODE))
		{
			if (character1.inSuperGodMode)
			{
				character1.inSuperGodMode = false;
				body1.gravity = 9.81f;
			}
			else
			{
				character1.inSuperGodMode = true;
				body1.gravity = 0;
			}
			
		}

		if (ae.mInputManager->isKeyTriggered(controller.NEXT_LEVEL))
		{
			ae.mLevelManager->loadNextLevel();
		}
		else if (ae.mInputManager->isKeyTriggered(controller.PREV_LEVEL))
		{
			ae.mLevelManager->loadPreviosLevel();
		}
		else if (ae.mInputManager->isKeyTriggered(controller.ED_LEVEL))
		{
			ae.mLevelManager->loadLevel(ED_LEVELS);
		}
		else if (ae.mInputManager->isKeyTriggered(controller.FINAL_LEVEL))
		{
			ae.mLevelManager->loadLevel(ED_LEVELS - 1);
		}
		if (ae.mInputManager->isKeyTriggered(controller.IDIE))
		{
			health1.health = 0;
			health1.died = true;
			health2.health = 0;
			health2.died = true;
		}

		if (ae.mInputManager->isKeyTriggered(controller.LEFT))
		{
			//auto& body = ae.getComponent<PhysicsBodyComponent>(activeEntity);
			body1.velocityX = -1;
			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.RIGHT))
		{
			body1.velocityX = 1;
			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.UP) && !character1.inSuperGodMode)
		{
			/// AUDIO EVENT
			Event e(EventID::E_AUDIO_PLAY);
			e.setParam<string>(EventID::P_AUDIO_PLAY_AUDIOLOC,sfxJump);
			e.setParam<ChannelGroupTypes>(EventID::P_AUDIO_PLAY_CHANNELGROUP,ChannelGroupTypes::C_SFX);
			e.setParam<float>(EventID::P_AUDIO_PLAY_VOLUMEDB, 0.8f);
			ae.sendEvent(e);

			//Jump
			if (body1.grounded)
			{
				if(character1.isBig)
					body1.totalForceY = 0.2f;
				else
					body1.totalForceY = 3.0f;


				if (character1.canDoubleJump.isEnabled)
				{
					character1.canDoubleJump.isActive = true;
				}
			}

			//Wall Jump
			else if (character1.canWallJump.isEnabled && character1.canWallJump.isActive)
			{
				//colliding with right side of a wall
				if (ae.mInputManager->isKeyPressed(controller.LEFT))
				{
					body1.velocityX = 1;
					character1.canWallJump.isActive = false;
				}
				else if (ae.mInputManager->isKeyPressed(controller.RIGHT))
				{
					body1.velocityX = -1;
					character1.canWallJump.isActive = false;
				}
				//Double Jump
				else if (character1.canDoubleJump.isEnabled && character1.canDoubleJump.isActive)
				{
					character1.canDoubleJump.isActive = false;
				}
				body1.velocityY = 0;
				body1.totalForceY = 3;
			}

			//Double Jump
			else if (character1.canDoubleJump.isEnabled && character1.canDoubleJump.isActive)
			{
				body1.velocityY = 0;
				body1.totalForceY = 3;
				character1.canDoubleJump.isActive = false;
			}


			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.SWAP_CHARACTER) && !health2.died)
		{
			ATOM_INFO("SWAP_CHARACTER : {}", activeEntity);


			auto& controllerInactive = ae.getComponent<ControllerComponent>(inactiveEntity);

			controller.isActive = FALSE;
			controllerInactive.isActive = TRUE;

			ae.getComponent<ShootComponent>(activeEntity).isShooting = false;
			ae.getComponent<ShootComponent>(inactiveEntity).isShooting = false;
		}

		if (ae.mInputManager->isKeyTriggered(controller.SWAP_POSITION) && !health2.died)
		{
			ATOM_INFO("SWAP_POSITION : {}", activeEntity);

			auto& t1 = ae.getComponent<TransformComponent>(activeEntity);
			auto& t2 = ae.getComponent<TransformComponent>(inactiveEntity);

			body1.prevPositionX = t2.position.x;
			body1.prevPositionY = t2.position.y;
			body2.prevPositionX = t1.position.x;
			body2.prevPositionY = t1.position.y;

			body1.prevScaleX = t2.scale.x;
			body1.prevScaleY = t2.scale.y;
			body2.prevScaleX = t1.scale.x;
			body2.prevScaleY = t1.scale.y;

			//s(smaller), g(greater)
			//g s.y + g.y / 2
			//s s.y/2

			//s g.y + s.y/2
			//g g.y/2

			glm::vec3 temp1 = t1.position + glm::vec3(0, ((t2.scale.y + t1.scale.y) / 2.0f), 0);
			glm::vec3 temp2 = t2.position + glm::vec3(0, ((t1.scale.y + t2.scale.y) / 2.0f), 0);

			t1.position = temp2;
			t2.position = temp1;

			auto& controllerInactive = ae.getComponent<ControllerComponent>(inactiveEntity);

			controller.isActive = FALSE;
			controllerInactive.isActive = TRUE;

			ae.getComponent<ShootComponent>(activeEntity).isShooting = false;
			ae.getComponent<ShootComponent>(inactiveEntity).isShooting = false;
		}
	}

	{//Pressed

			if (ae.mInputManager->isKeyPressed(controller.UP) && character1.inSuperGodMode)
			{
					body1.velocityY = 1;
			}
			if (ae.mInputManager->isKeyPressed(controller.DOWN) && character1.inSuperGodMode)
			{
					body1.velocityY = -1;
			}

			if (ae.mInputManager->isKeyPressed(controller.LEFT))
			{
					body1.velocityX = -1;
			}

			if (ae.mInputManager->isKeyPressed(controller.RIGHT))
			{
					body1.velocityX = 1;
			}

	}

	{//Released

			if (ae.mInputManager->isKeyReleased(controller.UP) && character1.inSuperGodMode)
			{
				body1.velocityY = 0;
			}
			if (ae.mInputManager->isKeyReleased(controller.DOWN) && character1.inSuperGodMode)
			{
				body1.velocityY = 0;
			}

			if (ae.mInputManager->isKeyReleased(controller.LEFT))
			{
				body1.velocityX = 0;
			}
			if (ae.mInputManager->isKeyReleased(controller.RIGHT))
			{
				body1.velocityX = 0;
			}

	}





}

void ControllerSystem::onEvent(Event& e)
{
	// play audio event
	if (e.getType() == EventID::E_AUDIO_PLAY) {
		auto audioloc = e.getParam<string>(EventID::P_AUDIO_PLAY_AUDIOLOC);
		auto chgroup = e.getParam<ChannelGroupTypes>(EventID::P_AUDIO_PLAY_CHANNELGROUP);
		auto volumedb = e.getParam<float>(EventID::P_AUDIO_PLAY_VOLUMEDB);
		ae.play(audioloc, chgroup, std::clamp(volumedb,0.0f,1.0f));
	}

	else if (e.getType() == EventID::E_COLLISION) {
		EntityID e1 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID1);
		EntityID e2 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID2);

		if (ae.hasComponent<CharacteristicComponent>(e1))
		{
			auto& characteristic = ae.getComponent<CharacteristicComponent>(e1);
			auto& body = ae.getComponent<PhysicsBodyComponent>(e1);
			if (body.grounded)
			{
				characteristic.canWallJump.isActive = false;
			}
			else
			{
				characteristic.canWallJump.isActive = true;
				characteristic.canDoubleJump.isActive = true;

			}
		}

		//both colliders can be player char, todo refractor
		if (ae.hasComponent<CharacteristicComponent>(e2))
		{
			auto& characteristic = ae.getComponent<CharacteristicComponent>(e2);
			auto& body = ae.getComponent<PhysicsBodyComponent>(e1);
			if (!body.grounded)
			{
				characteristic.canWallJump.isActive = true;
			}
			else
			{
				characteristic.canWallJump.isActive = false;
				characteristic.canDoubleJump.isActive = true;
			}
		}

	}
		
}