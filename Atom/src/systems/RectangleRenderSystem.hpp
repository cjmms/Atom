/*
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

class RectangleRenderSystem : public System {
public:

	// These 3 methods init,udate, onEvent must mandatorily be overriden by each system
	void init() override;
	void update() override;
	void onEvent(Event& e) override;


	// other methods in the system
	// pos is the top left vertex of the rectangle
	void draw(glm::vec2 pos, glm::vec2 scale, glm::vec3 color, bool wireframe=false) const;
	std::unique_ptr<Shader> RecShader;
	unsigned int RecVAO;
};

