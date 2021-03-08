#include "Pch.hpp"
#include "RectangleRenderSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"

#include "components/AllComponents.hpp"


// this is needed in all systems as the engine is in the Application.cpp translation unit 
extern AtomEngine ae;
bool DebugMode;


void RectangleRenderSystem::init() {
	DebugMode = false;

	// Background image
	//setBackground("Atom/res/level_01_background.png");

	worriorTimer = glfwGetTime();
	VampireTimer = glfwGetTime();
	laternTimer = glfwGetTime();

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


	if (ae.mInputManager->isKeyTriggered(ATOM_SCANCODE_T)) {
		DebugMode = !DebugMode;
	}

	// draw Background
	//draw(glm::vec2(0.0,0.0), glm::vec2(2.0f), BackgroundAddress);

	// draw all entities
	drawEntities(DebugMode);

	//for (auto& e : mEntities) {
	//	TagComponent& tag = ae.getComponent<TagComponent>(e);
	//	TransformComponent& t = ae.getComponent<TransformComponent>(e);

	//	if (tag.tag == "small player") {
	//		auto cam = getCameraPos();
	//		setCameraPos(glm::vec2{t.position.x,cam.y});
	//	}
	//}

	// animation demo
	//drawAnimation(glm::vec2(0.8, 0.8), glm::vec2(0.4f), "knightSlice", "png", 3, worriorTimer, DebugMode);

	//drawAnimation(glm::vec2(0.8, -0.8), glm::vec2(0.4f), "Vampire", "png", 4, VampireTimer, DebugMode);

	//drawAnimation(glm::vec2(-0.8, -0.8), glm::vec2(0.4f), "latern", "png", 4, laternTimer, DebugMode);
}



void RectangleRenderSystem::drawKeyFrame(glm::vec2 pos, glm::vec2 scale, std::string name, std::string type, int n, bool wireframe) const
{
	std::string address = "Atom/res/Animation/" + name + std::to_string(n) + "." + type;
	draw(pos, scale, address, false);
	if (wireframe) draw(pos, scale, address, true);
}



void RectangleRenderSystem::drawAnimation(glm::vec2 pos, glm::vec2 scale, std::string name, std::string type, int n, float &timer, bool wireframe) const
{
	float deltaTime = glfwGetTime() - timer;

	for (int i = 1; i <= n; ++i)
	{
		if (deltaTime < 0.1f * i) {
			drawKeyFrame(pos, scale, name, type, i - 1, wireframe);
			break;
		}
	}
	if (deltaTime > 0.1f * n)
	{
		drawKeyFrame(pos, scale, name, type, n - 1, wireframe);
		timer = glfwGetTime();
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
	
	ColorRecShader->SetInt("wireframe", wireframe);

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
	TextureRecShader->SetInt("wireframe", wireframe);

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


void RectangleRenderSystem::drawEntities(bool debugMode)
{
	for (auto& entity : mEntities) {
		if (ae.hasComponent<RectangleComponent>(entity)) {
			auto& rc = ae.getComponent<RectangleComponent>(entity);

			if (ae.hasComponent<TransformComponent>(entity)) {
				auto& t = ae.getComponent<TransformComponent>(entity);

				if (!rc.texturePath.empty())
					draw(glm::vec2{ t.position.x,t.position.y }, t.scale, rc.texturePath, false);
				else
					draw(glm::vec2{ t.position.x,t.position.y }, t.scale, rc.color, false);

				if (debugMode) draw(glm::vec2{ t.position.x,t.position.y }, t.scale, rc.color, true);
			}
		}
	}
}
