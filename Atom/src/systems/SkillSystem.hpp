/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		SkillSystem.hpp
* @author	Gerald Lee
* @brief	Contains logic for assigning skills to character based on respective triggers
* @date		2021-03-09
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class SkillSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
