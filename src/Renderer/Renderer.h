#pragma once



#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// pos is the top left vertex of the triangle
	void DrawRec(glm::vec2 pos, glm::vec2 scale, glm::vec3 color) const;

	inline void EnableFrameWireMode() const { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); };
	inline void DisableFrameWireMode() const { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); };


private:
	Shader* RecShader;
	unsigned int RecVAO;

	// set up VAP, VBO, EBO
	void RecSetup();
};

