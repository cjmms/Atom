#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "RectangleRenderSystem.hpp"
#include "utils/Log.hpp"
#include "components/ControllerComponent.hpp"
#include "components/PhysicsBodyComponent.hpp"
#include "components/TransformComponent.hpp"

//Temp

extern AtomEngine ae;

void ControllerSystem::init()
{
	/*ae.addEventListener(EventID::E_WINDOW_KEY_TRIGGERED, [this](Event& e) 
		{
			this->onEvent(e);
		});

	ae.addEventListener(EventID::E_WINDOW_KEY_PRESSED, [this](Event& e)
		{
			this->onEvent(e);
		});

	ae.addEventListener(EventID::E_WINDOW_KEY_RELEASED, [this](Event& e)
		{
			this->onEvent(e);
		});*/
}

void ControllerSystem::update()
{
	EntityID activeEntity;
	EntityID inactiveEntity;
	
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
	auto& body = ae.getComponent<PhysicsBodyComponent>(activeEntity);
	auto& controller = ae.getComponent<ControllerComponent>(activeEntity);

	{//Triggered

		if (ae.mInputManager->isKeyTriggered(controller.LEFT))
		{
			//auto& body = ae.getComponent<PhysicsBodyComponent>(activeEntity);
			body.velocityX = -1;
			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.RIGHT))
		{
			body.velocityX = 1;
			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.UP))
		{
			if(body.velocityY == 0)
				body.velocityY = 3;
			//ATOM_INFO("VELOCITY : {}", body.velocityX);
		}

		if (ae.mInputManager->isKeyTriggered(controller.SWAP_CHARACTER))
		{
			ATOM_INFO("SWAP_CHARACTER : {}", activeEntity);


			auto& controllerInactive = ae.getComponent<ControllerComponent>(inactiveEntity);

			controller.isActive = FALSE;
			controllerInactive.isActive = TRUE;
		}

		if (ae.mInputManager->isKeyTriggered(controller.SWAP_POSITION))
		{
			ATOM_INFO("SWAP_POSITION : {}", activeEntity);


			auto& b1 = ae.getComponent<PhysicsBodyComponent>(activeEntity);
			auto& b2 = ae.getComponent<PhysicsBodyComponent>(inactiveEntity);
			auto& t1 = ae.getComponent<TransformComponent>(activeEntity);
			auto& t2 = ae.getComponent<TransformComponent>(inactiveEntity);

			b1.prevPositionX = t2.position.x;
			b1.prevPositionY = t2.position.y;
			b2.prevPositionX = t1.position.x;
			b2.prevPositionY = t1.position.y;

			b1.prevScaleX = t2.scale.x;
			b1.prevScaleY = t2.scale.y;
			b2.prevScaleX = t1.scale.x;
			b2.prevScaleY = t1.scale.y;

			//s(smaller), g(greater)
			//g s.y + g.y / 2
			//s s.y/2

			//s g.y + s.y/2
			//g g.y/2

			glm::vec3 temp1 = t1.position + glm::vec3(0, ((t2.scale.y + t1.scale.y) / 2.0f), 0);
			glm::vec3 temp2 = t2.position + glm::vec3(0, ((t1.scale.y + t2.scale.y) / 2.0f), 0);

			t1.position = temp2;
			t2.position = temp1;

			/*

			t1.position.y = t1.position.y - t1.scale.y / 2 + t2.scale.y / 2 ;
			t2.position.y = t2.position.y - t2.scale.y / 2 + t1.scale.y / 2;


			*/
		}
	}

	{//Pressed

			if (ae.mInputManager->isKeyPressed(controller.LEFT))
			{
				body.velocityX = -1;
			}

			if (ae.mInputManager->isKeyPressed(controller.RIGHT))
			{
				body.velocityX = 1;
			}

	}

	{//Released

			if (ae.mInputManager->isKeyReleased(controller.LEFT))
			{
				body.velocityX = 0;
			}
			if (ae.mInputManager->isKeyReleased(controller.RIGHT))
			{
				body.velocityX = 0;
			}

	}

	{//Mouse
		if (ae.mInputManager->isKeyPressed(VK_LBUTTON))
		{
			std::pair<double, double> dPosition = ae.mInputManager->getCursorPosChange();
			ATOM_INFO("Left Mouse Button is pressed, Change in Xposition : {}, Change in Yposition : {}",dPosition.first, dPosition.second);

			glm::vec2 cameraPos = ae.mSystemManager->getSystem<RectangleRenderSystem>()->getCameraPos();

			cameraPos.x -= dPosition.first / 200;
			cameraPos.y += dPosition.second / 200;

			ae.mSystemManager->getSystem<RectangleRenderSystem>()->setCameraPos(cameraPos);

			ATOM_INFO("Camera Position x : {} , y : {}", cameraPos.x, cameraPos.y);
		}
	}
}

void ControllerSystem::onEvent(Event& e)
{
	//if (e.getType() == EventID::E_WINDOW_KEY_TRIGGERED)
	//{
	//	switch (e.getParam<int>(P_WINDOW_KEY_TRIGGERED_KEYCODE))
	//	{
	//	case (VK_UP):
	//		//Jump
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//else if (e.getType() == EventID::E_WINDOW_KEY_PRESSED)
	//{
	//	switch (e.getParam<int>(P_WINDOW_KEY_PRESSED_KEYCODE))
	//	{
	//	case (VK_LEFT):
	//		//Move left
	//		break;
	//	case (VK_RIGHT):
	//		//Move right
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//else if (e.getType() == EventID::E_WINDOW_KEY_RELEASED)
	//{
	//	switch (e.getParam<int>(P_WINDOW_KEY_RELEASED_KEYCODE))
	//	{
	//	case (VK_ESCAPE):
	//		//Quit
	//		break;
	//	default:
	//		break;
	//	}
	//}
		
}


//if (ae.mInputManager->isKeyTriggered(controller.swap))
			//swapping entity-> small, entity->larger

			//if (ae.mInputManager->isKeyTriggered(controller.LEFT))
			//{
			//	auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			//	body.velocityX = -2;
			//	//ATOM_INFO("VELOCITY : {}", body.velocityX);
			//}

			//if (ae.mInputManager->isKeyTriggered(controller.RIGHT))
			//{
			//	auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			//	body.velocityX = 2;
			//	//ATOM_INFO("VELOCITY : {}", body.velocityX);
			//}

			//if (ae.mInputManager->isKeyTriggered(controller.UP))
			//{
			//	auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
			//	body.velocityY = 2;
			//	//ATOM_INFO("VELOCITY : {}", body.velocityX);