/*
* @file		TransformSystem.hpp
* @author	Abhikalp Unakal
* @brief	System to update model transform matrix
* @date		2021-01-27
*/

#ifndef TRANSFORMSYSTEM_HPP
#define TRANSFORMSYSTEM_HPP

#include "Pch.hpp"
#include "core/Shader.hpp"
#include "core/Event.hpp"
#include "core/System.hpp"

#include "systems/ParticleEffect/ParticleEffect.hpp"

#include "Pch.hpp"
#include "core/System.hpp"
class TransformSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};
#endif // !TRANSFORMSYSTEM_HPP