#include "Pch.hpp"
#include "RectangleRenderSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"

#include "components/AllComponents.hpp"


// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;



void RectangleRenderSystem::init() {
	// Background image
	// This is not the "Correct way" to implement
	// But it works for Engine Demo with minimal extra code
	setBackground("Atom/res/Background.jpg");

	timer = glfwGetTime();

	CameraPos = glm::vec2(0.0f);

	// init shaders
	ColorRecShader = std::make_unique<Shader> ("Atom/res/ColorRec.shader");
	TextureRecShader = std::make_unique<Shader>("Atom/res/TextureRec.shader");

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


void RectangleRenderSystem::update() {

	// draw Background
	draw(glm::vec2(-1.0, 1.0), glm::vec2(2.0f), BackgroundAddress);

	float deltaTime = glfwGetTime() - timer;

	if (deltaTime < 0.1f)
		drawAnimation(glm::vec2(0.0), glm::vec2(1.0f), "knightRun", "png", 0);
	else if (deltaTime < 0.2f)
		drawAnimation(glm::vec2(0.0), glm::vec2(1.0f), "knightRun", "png", 1);
	else if (deltaTime < 0.3f)
		drawAnimation(glm::vec2(0.0), glm::vec2(1.0f), "knightRun", "png", 2);
	else if (deltaTime < 0.4f)
		drawAnimation(glm::vec2(0.0), glm::vec2(1.0f), "knightRun", "png", 3);
	else
		drawAnimation(glm::vec2(0.0), glm::vec2(1.0f), "knightRun", "png", 4);

	// set timer back
	if (deltaTime > 0.5f) timer = glfwGetTime();


	/*
	for (auto& entity : mEntities) {
		if (ae.hasComponent<RectangleComponent>(entity)) {
			auto& rc = ae.getComponent<RectangleComponent>(entity);

			if (ae.hasComponent<TransformComponent>(entity)) {
				auto& t = ae.getComponent<TransformComponent>(entity);
				glm::vec3 topleft = t.position - t.scale / 2.0f;

				if (!rc.texturePath.empty())
					draw(glm::vec2{ t.position.x,t.position.y }, t.scale, rc.texturePath, rc.wireframe);
				else
					draw(glm::vec2{ t.position.x,t.position.y }, t.scale, rc.color, rc.wireframe);
			}
		}
	}
	*/
}


void RectangleRenderSystem::drawAnimation(glm::vec2 pos, glm::vec2 scale, std::string name, std::string type, int n, bool wireframe) const
{
	std::string address = "Atom/res/" + name + std::to_string(n) + "." + type;
	draw(pos, scale, address, wireframe);
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

	ColorRecShader->SetVec2("pos", pos);
	ColorRecShader->SetVec2("scale", scale);
	ColorRecShader->SetVec3("color", color);

	ColorRecShader->SetVec2("cameraPos", CameraPos);

	ColorRecShader->Bind();
	glBindVertexArray(RecVAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}



void RectangleRenderSystem::draw(glm::vec2 pos, glm::vec2 scale, string texturePath, bool wireframe) const
{
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	TextureRecShader->SetVec2("pos", pos);
	TextureRecShader->SetVec2("scale", scale);
	
	TextureRecShader->SetVec2("cameraPos", CameraPos);

	// load texture
	unsigned int textureID = ae.getOrLoadResource<unsigned int>(texturePath);
	TextureRecShader->SetTexture("tex", textureID);

	TextureRecShader->Bind();
	glBindVertexArray(RecVAO);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
