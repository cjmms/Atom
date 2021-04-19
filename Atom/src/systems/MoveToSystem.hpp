/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		MoveToSystem.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Contains Logic for Movement on trigger action
* @date		2021-04-13
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class MoveToSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	std::vector<string> tags;
	float conversion_factor = 8.0f;
};