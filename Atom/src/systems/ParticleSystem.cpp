#include "Pch.hpp"
#include "ParticleSystem.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"

extern AtomEngine ae;

void ParticleSystem::init()
{
	// spawn center, spawn area size, spawn area shape
	SpawnConfig sCon(glm::vec2(0.0f),0.4f, AREA_MODE::SQUARE);
	// move direction, speed, move pattern
	MoveConfig mCon(glm::vec2(0.0, 1.0), 1.7f, DIR_MODE::CIRCULAR);
	// number of particles, particle size, time duration
	ParticleConfig pCon(20000, 0.6, glm::vec2(0.1f, 2.0f));

	ParticleEffect effect(sCon, mCon, pCon);
	effect.Init();
	ParticleEffects.push_back(effect);
}


void ParticleSystem::update()
{
	EntityID activeEntity;
	//ControllerComponent controller;

	//ParticleEffects[0].Draw();

	for (auto& entity : mEntities)
	{
		if (ae.hasComponent<ControllerComponent>(entity))
		{
			auto& controller = ae.getComponent<ControllerComponent>(entity);
			if (controller.isActive) activeEntity = entity;
		}
	}

	auto& transform = ae.getComponent<TransformComponent>(activeEntity);
	auto& controller = ae.getComponent<ControllerComponent>(activeEntity);

	if (ae.mInputManager->isKeyTriggered(controller.SWAP_POSITION))
	{
		//transform.position;
		
		ATOM_INFO("pressed");
	}
}


void ParticleSystem::onEvent(Event& e)
{

}