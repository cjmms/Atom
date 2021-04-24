/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AnimationSystem.hpp
* @author	Abhikalp Unakal
* @brief	Logic for Animation with respect to States of the Character
* @date		2021-04-12
*/

#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class AnimationSystem : public System{
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	void draw(glm::vec2 pos, glm::vec2 scale, string texturePath, bool wireframe, float alpha, glm::vec2 uv) const;

	//PlayerStates mPrevState = PlayerStates::PS_IDLE;
	//PlayerStates mCurrState = PlayerStates::PS_IDLE;

	//std::unique_ptr<Shader> TextureRecShader;
	//unsigned int RecVAO;
};

#endif