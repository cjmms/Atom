#include "Pch.hpp"
#include "ControllerSystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "components/ControllerComponent.hpp"
#include "components/PhysicsBodyComponent.hpp"

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
	for (auto& entity : mEntities) {
		if (ae.hasComponent<ControllerComponent>(entity)) 
		{
			if (ae.mInputManager->isKeyTriggered(VK_LEFT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = -2;
				//ATOM_INFO("VELOCITY : {}", body.velocityX);
			}

			if (ae.mInputManager->isKeyTriggered(VK_RIGHT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = 2;
				//ATOM_INFO("VELOCITY : {}", body.velocityX);
			}

			if (ae.mInputManager->isKeyTriggered(VK_UP))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityY = 2;
				//ATOM_INFO("VELOCITY : {}", body.velocityX);
			}
		}

		if (ae.hasComponent<ControllerComponent>(entity))
		{
			if (ae.mInputManager->isKeyPressed(VK_LEFT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = -2;
			}

			if (ae.mInputManager->isKeyPressed(VK_RIGHT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = 2;
			}
		}

		if (ae.hasComponent<ControllerComponent>(entity))
		{
			if (ae.mInputManager->isKeyReleased(VK_LEFT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = 0;

			}
			if (ae.mInputManager->isKeyReleased(VK_RIGHT))
			{
				auto& body = ae.getComponent<PhysicsBodyComponent>(entity);
				body.velocityX = 0;

			}
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