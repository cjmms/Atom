/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		RectangleRenderSystem.hpp
* @author	Xingyu Wang
* @brief	System to render rectangles
* @date		2021-01-27
*/

#pragma once

#include "Pch.hpp"
#include "core/Shader.hpp"
#include "core/Event.hpp"
#include "core/System.hpp"

//#include "systems/ParticleEffect/ParticleEffect.hpp"

class RectangleRenderSystem : public System {
public:

	// These 3 methods init,udate, onEvent must mandatorily be overriden by each system
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	inline void setBackground(std::string address) { BackgroundAddress = address; }

	// other methods in the system
	// pos is the top left vertex of the rectangle
	void draw(glm::vec2 pos, glm::vec2 scale, glm::vec3 color, bool wireframe=false, float alpha = 1.0) const;
	void draw(glm::vec2 pos, glm::vec2 scale, string texturePath, bool wireframe=false, float alpha = 1.0) const;

	void drawEntities(bool debugMode);

	void drawKeyFrame(glm::vec2 pos, glm::vec2 scale, std::string name, std::string type, int n, bool wireframe =false) const;
	void drawAnimation(glm::vec2 pos, glm::vec2 scale, std::string name, std::string type, int n, float &timer, bool wireframe=false) const;

	bool DebugMode;

private:
	std::unique_ptr<Shader> ColorRecShader;
	std::unique_ptr<Shader> TextureRecShader;
	unsigned int RecVAO;
	std::string BackgroundAddress;

	float worriorTimer;
	float VampireTimer;
	float laternTimer;

	//ParticleEffect* particleEffect;
};

