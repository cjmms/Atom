/*
* @file		RectangleRenderSystem.hpp
* @author	Gerald Lee
* @brief	System to render health bars
* @date		2021-03-07
*/

#pragma once

#include "Pch.hpp"
#include "core/Shader.hpp"
#include "core/Event.hpp"
#include "core/System.hpp"

class HealthRenderSystem : public System {
public:

	// These 3 methods init,udate, onEvent must mandatorily be overriden by each system
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	// other methods in the system
	// pos is the top left vertex of the rectangle
	void draw(glm::vec2 pos, glm::vec2 scale, glm::vec3 color, bool wireframe, float alpha) const;

	void drawEntities();

private:
	std::unique_ptr<Shader> ColorRecShader;
	unsigned int RecVAO;
	glm::vec2 CameraPos;
};

