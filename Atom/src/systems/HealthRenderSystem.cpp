#include "Pch.hpp"
#include "HealthRenderSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"

#include "components/HealthComponent.hpp"
#include "components/TransformComponent.hpp"


// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;

void HealthRenderSystem::init() {

	// init shaders
	ColorRecShader = std::make_unique<Shader>("Atom/res/shaders/ColorRec.shader");

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	   // positions   // texCoords
	   -0.5f,  0.5f,  0.0f, 1.0f,
	   -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  1.0f, 0.0f,

	   -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  1.0f, 1.0f
	};
	unsigned int quadVBO;

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &RecVAO);
	glBindVertexArray(RecVAO);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void HealthRenderSystem::update() {

	// draw all entities
	drawEntities();

}

void HealthRenderSystem::onEvent(Event& e) {

}

void HealthRenderSystem::drawEntities()
{
	glm::vec3 redColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 whiteColor = glm::vec3(1.0f, 1.0f, 1.0f);

	for (auto& entity : mEntities) {
		if (!ae.hasComponent<HealthComponent>(entity))
			return;
		if (!ae.hasComponent<TransformComponent>(entity))
			return;

		auto& h = ae.getComponent<HealthComponent>(entity);
		auto& t = ae.getComponent<TransformComponent>(entity);

		glm::vec2 position = glm::vec2(t.position.x + h.offsetX,t.position.y + h.offsetY + t.scale.y/2.0f);
		glm::vec2 size = glm::vec2(h.width * h.health / h.totalHealth, h.height);

		draw(position, glm::vec2{h.width, h.height}, whiteColor);
		float offsetX = (h.width - size.x) / 2.0;
		draw(glm::vec2{position.x-offsetX,position.y}, size, redColor);

	}
}

void HealthRenderSystem::draw(glm::vec2 pos, glm::vec2 scale, glm::vec3 color) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	ColorRecShader->SetInt("wireframe", false);

	ColorRecShader->SetVec2("pos", pos);
	ColorRecShader->SetVec2("scale", scale);
	ColorRecShader->SetVec3("color", color);

	ColorRecShader->SetVec2("cameraPos", ae.mCameraManager->getPosition());

	ColorRecShader->Bind();
	glBindVertexArray(RecVAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}
