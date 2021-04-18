/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AutoMovementSystem.hpp
* @author	Gerald Lee
* @brief	Logic for horizontal movement of bots
* @date		2021-03-19
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class AutoMovementSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};