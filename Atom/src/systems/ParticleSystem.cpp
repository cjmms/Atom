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
			auto p = ae.getComponent<ParticleComponent>(entity);
			p.sCon.areaCenter = glm::vec2{ t.position.x,t.position.y };
			p.pE->Draw(p.sCon.areaCenter);
		}
	}

}
void ParticleSystem::onEvent(Event& e) {

}
