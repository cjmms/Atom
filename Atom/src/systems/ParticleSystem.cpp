/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		ParticleSystem.cpp
* @author	Abhikalp Unakal
* @brief	System to orchestrate particle effects
* @date		2021-04-10
*/

#include "Pch.hpp"
#include "ParticleSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"
#include "components/AllComponents.hpp"

// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;

void ParticleSystem::init() {

}


void ParticleSystem::update() {

	for (auto& entity : mEntities){
		if (ae.hasComponent<TransformComponent>(entity) && ae.hasComponent<ParticleComponent>(entity)) {
			auto& t = ae.getComponent<TransformComponent>(entity);
			auto& p = ae.getComponent<ParticleComponent>(entity);

			p.sCon.areaCenter = glm::vec2{ t.position.x - 0.1,t.position.y - 0.1 };
			p.pE.Draw(p.sCon.areaCenter);

			//std::cout << "draw particle" << std::endl;
		}
	}

}
void ParticleSystem::onEvent(Event& e) {

}
