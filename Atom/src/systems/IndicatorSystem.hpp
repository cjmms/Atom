/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		IndicatorSystem.hpp
* @author	Gerald Lee
* @brief	indicates current controlling character
* @date		2021-04-12
*/

#pragma once

#include "Pch.hpp"
#include "core/Shader.hpp"
#include "core/Event.hpp"
#include "core/System.hpp"

class IndicatorSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
