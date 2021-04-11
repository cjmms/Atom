/*
* @file		ParticleComponent.hpp
* @author	Abhikalp Unakal
* @brief	used to specify attributes of the particle system
* @date		2021-04-10
*/

#ifndef PARTICLECOMPONENT_HPP
#define PARTICLECOMPONENT_HPP

#include <Pch.hpp>
#include "core/Types.hpp"
#include "utils/Serde.hpp"
#include "systems/ParticleEffect/ParticleEffect.hpp"

class ParticleComponent {
public:
	// number of particles, size of particles, time
	ParticleConfig pCon = ParticleConfig(30, 0.3, glm::vec2(0.1f, 2.0f));
	// spawn center, spawn area size, spawn area shape
	SpawnConfig sCon = SpawnConfig(glm::vec2(-0.8f, -0.8), 0.1f, AREA_MODE::SQUARE);
	// move direction, speed, move pattern
	MoveConfig mCon = MoveConfig(glm::vec2(0.0, 1.0), 0.01f, DIR_MODE::CIRCULAR);

	ParticleEffect pE = ParticleEffect(sCon, mCon, pCon);
	ParticleComponent() {
		pE.Init();
	}
};

// RENDERBOX COMPONENT SERDE
inline void to_json(ordered_json& j, const ParticleComponent& x) {
	//to_json(j["color"], x.color);
}

inline void from_json(const ordered_json& j, ParticleComponent& x) {
	//from_json(j["color"], x.color);
}

#endif