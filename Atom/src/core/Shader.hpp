/*
* @file		Shader.hpp
* @author	Xingyu Wang
* @brief	Shader class
* @date		2021-01-06
*/

#pragma once
#include "Pch.hpp"
#include "core/Types.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
	std::string GeometrySource;
	std::string ComputeSource;
};


class Shader
{
private:
	std::string shaderFilePath;

	// program ID of shader
	unsigned int rendererID;
	unsigned int textureUnit;
	std::vector<std::string> textures;

public:
	Shader() :rendererID(0) {};
	Shader(const std::string& path);
	~Shader();
	void Bind();
	void UnBind();
	int GetUniformLocation(const char* name);
	unsigned int GetRendererID();

	void SetMat4(const char* name, glm::mat4 matrix);
	void SetMat4(const std::string& name, glm::mat4 matrix);
	void SetVec3(const char* name, glm::vec3 vec);
	void SetVec3(const std::string& name, glm::vec3 vec);
	void SetVec2(const char* name, glm::vec2 vec);
	void SetVec2(const std::string& name, glm::vec2 vec);
	void SetFloat(const char* name, float value);
	void SetFloat(const std::string& name, float value);

	void SetInt(const char* name, int value);
	void SetInt(const std::string& name, int value);

	void SetTexture(const char* name, unsigned int texture);
	void SetTexture(const std::string& name, unsigned int texture, int index = -1);

private:
	// path: res/Shaders/basic.shader
	// path is relative a path
	// absolute path is ($SolutionDir)path
	ShaderProgramSource ParseShader(const std::string& path);

	// type: GL_FRAGMENT_SHADER or GL_VERTEX_SHADER
	// return shader program ID
	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
	void ShaderErrorInfo(unsigned int shader, unsigned int type);

	// vertexShader: shader source as a string
	// fragmentShader: shader source as a string
	// return shader ID
	unsigned int CreateShader(const std::string& vertexShader,
		const std::string& fragmentShader,
		const std::string& geometryShader,
		const std::string& computeShader);
};