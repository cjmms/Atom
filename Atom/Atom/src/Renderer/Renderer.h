#pragma once

#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer() {};

	void DrawRec(glm::vec2 pos, glm::vec2 scale, glm::vec3 color) const;


private:
	Shader* basic;

};

