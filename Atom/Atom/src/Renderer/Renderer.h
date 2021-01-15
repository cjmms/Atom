#pragma once

#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void DrawRec(glm::vec2 pos, glm::vec2 scale, glm::vec3 color) const;

	inline void EnableFrameWireMode() const { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); };
	inline void DisableFrameWireMode() const { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); };


private:
	Shader* basic;
	unsigned int Rec_VAO;

	// set up VAP, VBO, EBO
	void RecSetup();
};

