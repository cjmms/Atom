/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		PushUpSystem.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Contains logic for entities that constantly apply a constant force
* @date		2021-07-07
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class PushUpSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	EntityID BigChar = -1;
	float scale = 0.125f;

};