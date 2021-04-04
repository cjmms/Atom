#include "Pch.hpp"

#include "RenderTextComponent.hpp"
//
//void RenderText::init(FT_Face face)
//{
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	for (unsigned char c = 0; c < 128; c++)
//	{
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//		{
//			ATOM_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
//			continue;
//		}
//
//		unsigned int texture;
//
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//
//		//generate texture
//		glTexImage2D(
//			GL_TEXTURE_2D,
//			0,
//			GL_RED,
//			face->glyph->bitmap.width,
//			face->glyph->bitmap.rows,
//			0,
//			GL_RED,
//			GL_UNSIGNED_BYTE,
//			face->glyph->bitmap.buffer
//		);
//
//		//setting options
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		//storing charecter
//		Charecter charecter = {
//			texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			face->glyph->advance.x
//		};
//
//		Charecters.insert(std::pair<char, Charecter>(c, charecter));
//	}
//}