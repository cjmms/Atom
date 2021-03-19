/*
* @file		DamageSystem.hpp
* @author	Gerald Lee
* @brief	for handling bullet damage
* @date		2021-03-07
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

//shoot; involve instantiation of new game object

class DamageSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
