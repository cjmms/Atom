/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
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