#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"
#include "systems/ParticleEffect/ParticleEffect.hpp"

class ParticleSystem : public System
{
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	// temp solution to init particle effects
	std::vector<ParticleEffect> ParticleEffects;
};

