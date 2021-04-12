#include "Pch.hpp"
#include "ParticleSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"
#include "components/AllComponents.hpp"

// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;

EntityID box;

void ParticleSystem::init() {
	//box = ae.createEntity();
	//ae.addComponent<RectangleComponent>(box, RectangleComponent{
	//	glm::vec3{0,1,0},
	//	false,
	//	""
	//});
}


void ParticleSystem::update() {

	for (auto& entity : mEntities){
		//if (ae.hasComponent<TransformComponent>(entity) && ae.hasComponent<ParticleComponent>(entity)) {
		//	auto& t = ae.getComponent<TransformComponent>(entity);
		//	auto& p = ae.getComponent<ParticleComponent>(entity);
		//	p.sCon.areaCenter = glm::vec2{ t.position.x,t.position.y };



		//	// TODO : fix this part shows static white dots instead of changing the position every frame
		//	p.pE->Draw(p.sCon.areaCenter);
		//}
	}

}
void ParticleSystem::onEvent(Event& e) {

}
