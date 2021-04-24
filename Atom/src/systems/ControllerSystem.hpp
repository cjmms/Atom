/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ControllerSystem.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Contains logic for character reaction to controls and any other logic regarding for Player Character
* @date		date 2021-02-03
*/

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
