/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
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
	// spawn center, spawn area size, spawn area shape
	// move direction, speed, move pattern

	ParticleConfig pCon;
	SpawnConfig sCon;
	MoveConfig mCon;
	ParticleEffect* pE;

	ParticleComponent() : pCon(ParticleConfig(50, 0.1f, glm::vec2(0.1f, 2.0f))), 
		sCon(SpawnConfig(glm::vec2(100.0f,100.0f), 0.01f, AREA_MODE::CIRCLE)), 
		mCon(MoveConfig(glm::vec2(0.0,0.0f), 0.001f, DIR_MODE::CIRCULAR)),
		pE(new ParticleEffect(sCon,mCon,pCon))
	{
		pE->Init();
	}
	~ParticleComponent() {
		
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