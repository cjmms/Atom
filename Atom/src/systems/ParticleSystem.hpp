/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ParticleSystem.hpp
* @author	Abhikalp Unakal
* @brief	System to orchestrate particle effects
* @date		2021-04-10
*/

#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "Pch.hpp"
#include "core/Shader.hpp"
#include "core/Event.hpp"
#include "core/System.hpp"
#include "systems/ParticleEffect/ParticleEffect.hpp"

class ParticleSystem : public System {
public:

	// These 3 methods init,udate, onEvent must mandatorily be overriden by each system
	void init() override;
	void update() override;
	void onEvent(Event& e) override;


private:
	std::unique_ptr<Shader> ColorRecShader;
	unsigned int RecVAO;
	ParticleEffect* particleEffect;
};



#endif