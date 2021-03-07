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
