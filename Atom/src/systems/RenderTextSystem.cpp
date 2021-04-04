/*
* @file		RenderTextSystem.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	RenderTextSystem
* @date		2021-03-03
*/

#include "Pch.hpp"
#include "components/RenderTextComponent.hpp"

#include "RenderTextSystem.hpp"
#include <glm/gtc/matrix_transform.hpp>

void RenderTextSystem::init()
{
//	FT_Library ft;
//
//	if (FT_Init_FreeType(&ft))
//	{
//		ATOM_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
//		return;
//	}
//
//	FT_Face face;
//
//	if (FT_New_Face(ft, "Atom/res/arial.ttf", 0, &face))
//	{
//		ATOM_ERROR("ERROR::FREETYPE: Failed to load font");
//		return;
//	}
//
//	FT_Set_Pixel_Sizes(face, 0, 48);
//
//	renderText.init(face);
//
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//
//	//VAO and VBO
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	//Shader Init
//	//renderTextShader = std::make_unique<Shader>("Atom/res/renderText.shader");
//
//	//Projection
//	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
//
}
//
void RenderTextSystem::displayText(std::string text, float x, float y, float scale, glm::vec3 color)
{
//	Shader render("Atom/res/renderText.shader");
//
//	glUniformMatrix4fv(glGetUniformLocation(render.GetRendererID(), "projection"), sizeof(projection), GL_FALSE, &projection[0][0]);
//
//	glUniform3f(glGetUniformLocation(render.GetRendererID(), "textColor"), color.x, color.y, color.z);
//	glActiveTexture(GL_TEXTURE5);
//	glBindVertexArray(VAO);
//
//	std::string::const_iterator c;
//
//	for (c = text.begin(); c != text.end(); c++)
//	{
//		Charecter ch = renderText.Charecters[*c];
//
//		float xPosition = x + ch.bearing.x * scale;
//		float yPosition = y - (ch.size.y = ch.bearing.y) * scale;
//
//		float width = ch.size.x * scale;
//		float height = ch.size.y * scale;
//
//		float vertices[6][4] = {
//			{ xPosition			, yPosition + height, 0.0f, 0.0f},
//			{ xPosition			, yPosition			, 0.0f, 1.0f},
//			{ xPosition + width	, yPosition			, 1.0f, 1.0f},
//
//			{ xPosition			, yPosition + height, 0.0f, 0.0f},
//			{ xPosition + width	, yPosition			, 1.0f, 1.0f},
//			{ xPosition	+ width	, yPosition + height, 1.0f, 0.0f},
//		};
//
//		glBindTexture(GL_TEXTURE_2D, ch.textureId);
//
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//
//		x += (ch.advance >> 6) * scale;
//	}
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	//renderTextShader->UnBind();
}
