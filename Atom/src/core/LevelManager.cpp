#include <Pch.hpp>
#include "LevelManager.hpp"
#include "AtomEngine.hpp"

extern AtomEngine ae;

LevelManager::LevelManager()
{

}

void LevelManager::init()
{
	ae.addEventListener(EventID::E_COLLISION, [this](Event& e) {this->onEvent(e); });
}

void LevelManager::update()
{
	if (restartLevel)
	{
		restartLevel = false;
		ae.unload();
		ae.load("level_01.json");
	}
}

void LevelManager::onEvent(Event& e)
{
	if (e.getType() == EventID::E_COLLISION) {
		EntityID e1 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID1);
		EntityID e2 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID2);

		EntityID player = -1;

		bool enteredDeadZone = false;

		if (ae.hasComponent<ControllerComponent>(e1))
		{
			player = e1;
			if (ae.hasComponent<TagComponent>(e2) && ae.getComponent<TagComponent>(e2).tag == "DeadZone")
			{
				enteredDeadZone = true;
			}
		}
		else if (ae.hasComponent<ControllerComponent>(e2))
		{
			player = e2;
			if (ae.hasComponent<TagComponent>(e1) && ae.getComponent<TagComponent>(e1).tag == "DeadZone")
			{
				enteredDeadZone = true;
			}
		}

		if (!enteredDeadZone)
			return;

		restartLevel = true;
	}
}
