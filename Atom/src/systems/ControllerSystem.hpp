#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"
#include "components/CharacteristicComponent.hpp"

class ControllerSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	bool shouldFollow;
	bool isTriggered;


	glm::vec2 playerPosition;
};
