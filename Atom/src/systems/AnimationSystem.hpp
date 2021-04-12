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

	void draw(glm::vec2 pos, glm::vec2 scale, string texturePath, bool wireframe, float alpha) const;

	//PlayerStates mPrevState = PlayerStates::PS_IDLE;
	//PlayerStates mCurrState = PlayerStates::PS_IDLE;

	//std::unique_ptr<Shader> TextureRecShader;
	//unsigned int RecVAO;
};

#endif