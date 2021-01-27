#include "Pch.hpp"
#include "RectangleRenderSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"
#include "components/RectangleComponent.hpp"

// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;

void RectangleRenderSystem::init() {
	// init shaders
	RecShader = std::make_unique<Shader> ("Atom/res/Rectangle.shader");

	// setup shapes
	// set up VAP, VBO, EBO
	unsigned int VBO, EBO;

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  // bottom left
	   -0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// VAO
	glGenVertexArrays(1, &RecVAO);
	glBindVertexArray(RecVAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


void RectangleRenderSystem::update() {
	for (auto& entity : mEntities) {
		if (ae.hasComponent<RectangleComponent>(entity)) {
			auto& rc = ae.getComponent<RectangleComponent>(entity);
			draw(rc.position, rc.scale, rc.color, rc.wireframe);
		}
	}
}


void RectangleRenderSystem::onEvent(Event& e) {

}


void RectangleRenderSystem::draw(glm::vec2 pos, glm::vec2 scale, glm::vec3 color, bool wireframe) const
{

	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	RecShader->SetVec2("pos", pos);
	RecShader->SetVec2("scale", scale);
	RecShader->SetVec3("color", color);

	RecShader->Bind();
	glBindVertexArray(RecVAO);

	// The last arg is 0 since we do provide an EBO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}