/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		TransformSystem.cpp
* @author	Abhikalp Unakal
* @brief	System to update model transform matrix
* @date		2021-01-27
*/

#include "Pch.hpp"
#include "TransformSystem.hpp"
#include "core/AtomEngine.hpp"
#include "components/TransformComponent.hpp"
#include "glm/gtx/transform.hpp"

extern AtomEngine ae;

void TransformSystem::init() {

	//ae.addEventListener(EventID::E_BROADCAST_EVENT, std::bind(&TransformSystem::onEvent, this, std::placeholders::_1));
}

void TransformSystem::update() {
	for (auto& entity : mEntities) {
		auto& transformComponent = ae.getComponent<TransformComponent>(entity);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transformComponent.position);

		model = glm::translate(model, glm::vec3(0.5f * transformComponent.scale.x, 0.5f * transformComponent.scale.y, 0.0f));
		model = glm::rotate(model, glm::radians(transformComponent.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * transformComponent.scale.x, -0.5f * transformComponent.scale.y, 0.0f));

		model = glm::scale(model, transformComponent.scale);

		transformComponent.model = model;
	}
}

void TransformSystem::onEvent(Event& e) {

}