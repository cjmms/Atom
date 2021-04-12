#include "Pch.hpp"
#include "systems/AnimationSystem.hpp"
#include "core/AtomEngine.hpp"
#include "components/TransformComponent.hpp"
#include "components/AnimationComponent.hpp"

extern AtomEngine ae;

void AnimationSystem::init(){
	//TextureRecShader = std::make_unique<Shader>("Atom/res/shaders/TextureRec.shader");
	//float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
 //  // positions   // texCoords
 //  -0.5f,  0.5f,  0.0f, 1.0f,
 //  -0.5f, -0.5f,  0.0f, 0.0f,
	//0.5f, -0.5f,  1.0f, 0.0f,

 //  -0.5f,  0.5f,  0.0f, 1.0f,
	//0.5f, -0.5f,  1.0f, 0.0f,
	//0.5f,  0.5f,  1.0f, 1.0f
	//};
	//unsigned int quadVBO;

	//glGenBuffers(1, &quadVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

	//glGenVertexArrays(1, &RecVAO);
	//glBindVertexArray(RecVAO);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);
}

void AnimationSystem::update(){
	//for (auto& entity : mEntities) {
	//	if (ae.hasComponent<TransformComponent>(entity) && ae.hasComponent<AnimationComponent>(entity)) {
	//		auto& t = ae.getComponent<TransformComponent>(entity);
	//		auto& a = ae.getComponent<AnimationComponent>(entity);

	//		bool debugmode = ae.mIsDebugMode;
	//		float alpha = ae.mLevelManager->level_alpha;
	//		draw(glm::vec2{ t.position.x,t.position.y }, glm::vec2{ t.scale.x,t.scale.y }, a.spriteloc, debugmode, alpha);

	//	}
	//}
	//mPrevState = mCurrState;
}

void AnimationSystem::draw(glm::vec2 pos, glm::vec2 scale, string texturePath, bool wireframe, float alpha) const
{
//	if (wireframe) {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	}
//	else {
//		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	}
//	TextureRecShader->SetInt("wireframe", wireframe);
//	TextureRecShader->SetFloat("alpha", alpha);
//	TextureRecShader->SetVec2("pos", pos);
//	TextureRecShader->SetVec2("scale", scale);
//
//	TextureRecShader->SetVec2("cameraPos", ae.mCameraManager->camera.position);
//
//	TextureRecShader->SetMat4("projection", ae.mCameraManager->GetProjectionMatrix());
//
//	// load texture
//	unsigned int textureID = ae.getOrLoadResource<unsigned int>(texturePath);
//	TextureRecShader->SetTexture("tex", textureID);
//
//	TextureRecShader->Bind();
//	glBindVertexArray(RecVAO);
//
//	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void AnimationSystem::onEvent(Event& e){

}
