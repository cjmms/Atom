/*
* @file		IndicatorSystem.hpp
* @author	Gerald Lee
* @brief	indicates current controlling character
* @date		2021-04-12
*/

#include "Pch.hpp"
#include "IndicatorSystem.hpp"
#include "core/AtomEngine.hpp"
#include "components/TransformComponent.hpp"
#include "glm/gtx/transform.hpp"

extern AtomEngine ae;

void IndicatorSystem::init() {

}

void IndicatorSystem::update() {

	auto& players = ae.mSystemManager->getSystem<ControllerSystem>()->mEntities;
	if (players.size() == 0)
		return;

	EntityID activeCharacter = -1;
	EntityID indicator = -1;

	//should only has one entity
	for (auto& entity : mEntities)
	{
		indicator = entity;
	}

	if (indicator == -1)
		return;

	//loop through player characters and find active one
	for (auto itr = players.begin(); itr != players.end(); ++itr)
	{
		//auto& targetTransform = ae.getComponent<TransformComponent>(autoShoot.target);
		auto& controller = ae.getComponent<ControllerComponent>(*itr);
		if (controller.isActive)
		{
			activeCharacter = *itr;
		}
	}

	if (activeCharacter == -1)
		return;

	//update position of indicator based on active character
	auto& characterTransform = ae.getComponent<TransformComponent>(activeCharacter);
	auto& indicatorTransform =  ae.getComponent<TransformComponent>(indicator);

	auto offset = characterTransform.scale;
	offset.x = 0;
	offset.y = offset.y;
	indicatorTransform.position = characterTransform.position + offset;
}

void IndicatorSystem::onEvent(Event& e) {

}