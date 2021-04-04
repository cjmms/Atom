/*
* @file		RenderTextSystem.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	RenderTextSystem
* @date		2021-03-03
*/

#pragma once

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"
#include "core/Shader.hpp"

class RenderText;

class RenderTextSystem : public System {
public:
	void init() override;
	inline void update() override {};
	inline void onEvent(Event& e) override {};

	void displayText(std::string text, float x, float y, float scale, glm::vec3 color);

	//RenderText renderText;

	glm::mat4 projection;

	unsigned int VAO;
	unsigned int VBO;

	//Shader renderTextShader = Shader("Atom/res/renderText.shader");
};