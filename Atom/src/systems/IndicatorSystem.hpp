
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
