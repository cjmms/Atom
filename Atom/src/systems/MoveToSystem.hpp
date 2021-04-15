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