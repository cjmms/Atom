#include "Pch.hpp"
#include "Shader.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& path)
    :rendererID(0), shaderFilePath(path), textureUnit(0)
{
    ShaderProgramSource source = ParseShader(shaderFilePath);

    rendererID = CreateShader(source.VertexSource,
        source.FragmentSource,
        source.GeometrySource,
        source.ComputeSource
    );
}

Shader::~Shader()
{
    glDeleteProgram(rendererID);
}



ShaderProgramSource Shader::ParseShader(const std::string& path)
{
    enum class ShaderMode {
        NONE = -1, VERTEX_MODE = 0, FRAGMENT_MODE = 1, GEOMETRY_MODE = 2, COMPUTE_MODE = 3
    };
    std::fstream stream(path);
    std::string line;

    // 3 string streams, one for vertex shader, one for fragment shader, one for geometry shader
    std::stringstream ss[4];
    ShaderMode currentMode = ShaderMode::NONE;

    // shader file has 2 lines: #shader fragment and #shader vertex 
    // if any or these lines are detected, switch mode, output to another stringstream
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentMode = ShaderMode::VERTEX_MODE;
            else if (line.find("fragment") != std::string::npos)
                currentMode = ShaderMode::FRAGMENT_MODE;
            else if (line.find("geometry") != std::string::npos)
                currentMode = ShaderMode::GEOMETRY_MODE;
            else if (line.find("compute") != std::string::npos)
            {
                currentMode = ShaderMode::COMPUTE_MODE;
            }
        }
        else
        {
            ss[(int)currentMode] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str() };
}


unsigned int Shader::CreateShader(const std::string& vertexShader,
    const std::string& fragmentShader,
    const std::string& geometryShader,
    const std::string& computeShader)
{
    bool hasVertexShader = vertexShader.length() > 0;
    bool hasFragmentShader = fragmentShader.length() > 0;
    bool hasGeometryShader = geometryShader.length() > 0;
    bool hasComputeShader = computeShader.length() > 0;


    unsigned int shaderProgram = glCreateProgram();
    unsigned int vertexShaderID;
    unsigned int fragmentShaderID;
    unsigned int geometryShaderID;
    unsigned int computeShaderID;

    if (hasVertexShader)
    {
        vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShader);
        glAttachShader(shaderProgram, vertexShaderID);
    }

    if (hasFragmentShader)
    {
        fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        glAttachShader(shaderProgram, fragmentShaderID);
    }


    if (hasGeometryShader) {
        geometryShaderID = CompileShader(GL_GEOMETRY_SHADER, geometryShader);
        glAttachShader(shaderProgram, geometryShaderID);
    }

    if (hasComputeShader) {
        computeShaderID = CompileShader(GL_COMPUTE_SHADER, computeShader);
        glAttachShader(shaderProgram, computeShaderID);
    }


    glLinkProgram(shaderProgram);

    GLint success;
    //glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    /*
    if (!success)
    {
        GLchar errorLog[1024] = { 0 };
        glGetProgramInfoLog(shaderProgram, 1024, NULL, errorLog);
        std::cout << "ERROR: Shader Linking Error." << errorLog << std::endl;
    }*/


    glValidateProgram(shaderProgram);
    /*
    success = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLchar errorLog[1024] = { 0 };
        glGetProgramInfoLog(shaderProgram, 1024, NULL, errorLog);
        std::cout << "ERROR: Shader Validation Error." << errorLog << std::endl;
    }*/





    if (hasVertexShader) glDeleteShader(vertexShaderID);
    if (hasFragmentShader) glDeleteShader(fragmentShaderID);
    if (hasGeometryShader) glDeleteShader(geometryShaderID);
    if (hasComputeShader) glDeleteShader(computeShaderID);

    return shaderProgram;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
{
    unsigned int id = glCreateShader(type);
    const char* source = shaderSource.c_str();

    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    ShaderErrorInfo(id, type);
    return id;
}

void Shader::ShaderErrorInfo(unsigned int shader, unsigned int type)
{
    GLint success;
    char infoLog[512];
    // success is a flag, it will be set to False if things went wrong
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        if (type == GL_VERTEX_SHADER)
            std::cout << "ERROR: Vertex Shader Compilation Error. " << infoLog << std::endl;
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "ERROR: Fragment Shader Compilation Error. " << infoLog << std::endl;
        else if (type == GL_GEOMETRY_SHADER)
            std::cout << "ERROR: Geometry Shader Compilation Error. " << infoLog << std::endl;
        else
            std::cout << "ERROR: Compute Shader Compilation Error." << infoLog << std::endl;
    }
}

void Shader::Bind()
{
    glUseProgram(rendererID);
}

void Shader::UnBind()
{
    glUseProgram(0);
}


int Shader::GetUniformLocation(const char* name)
{
    return glGetUniformLocation(rendererID, name);
}

unsigned int Shader::GetRendererID()
{
    return rendererID;
}


void Shader::SetMat4(const char* name, glm::mat4 matrix)
{
    this->Bind();
    unsigned int location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    this->UnBind();
}


void Shader::SetMat4(const std::string& name, glm::mat4 matrix)
{
    SetMat4(name.c_str(), matrix);
}



void Shader::SetVec3(const char* name, glm::vec3 vec)
{
    this->Bind();
    unsigned int location = GetUniformLocation(name);
    glUniform3fv(location, 1, glm::value_ptr(vec));
    this->UnBind();
}


void Shader::SetVec3(const std::string& name, glm::vec3 vec)
{
    SetVec3(name.c_str(), vec);
}



void Shader::SetVec2(const char* name, glm::vec2 vec)
{
    this->Bind();
    unsigned int location = GetUniformLocation(name);
    glUniform2fv(location, 1, glm::value_ptr(vec));
    this->UnBind();
}


void Shader::SetVec2(const std::string& name, glm::vec2 vec)
{
    SetVec2(name.c_str(), vec);
}



void Shader::SetFloat(const char* name, float value)
{
    this->Bind();
    unsigned int location = GetUniformLocation(name);
    glUniform1f(location, value);
    this->UnBind();
}



void Shader::SetFloat(const std::string& name, float value)
{
    SetFloat(name.c_str(), value);
}



void Shader::SetInt(const char* name, int value)
{
    this->Bind();
    unsigned int location = GetUniformLocation(name);
    glUniform1i(location, value);
    this->UnBind();
}



void Shader::SetInt(const std::string& name, int value)
{
    SetInt(name.c_str(), value);
}


void Shader::SetTexture(const char* name, unsigned int texture)
{

    auto it = std::find(textures.begin(), textures.end(), name);

    // If element was found
    if (it != textures.end())
    {
        // calculating the index
        int index = it - textures.begin();

        this->SetInt(name, index);

        this->Bind();
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, texture);
        this->UnBind();
    }
    else {
        // If the element is not
        // present in the vector

        this->SetInt(name, textureUnit);

        this->Bind();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture);
        this->UnBind();

        textureUnit++;
        textures.push_back(name);
    }
}


void Shader::SetTexture(const std::string& name, unsigned int texture, int index)
{
    SetTexture(name.c_str(), texture, index);
}
