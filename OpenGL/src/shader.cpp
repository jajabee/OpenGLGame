#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    CreateShader(vertexPath, fragmentPath);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::Use()
{
    glUseProgram(id_);
}

void Shader::CreateShader(const char* vertexPath, const char* fragmentPath)
{
    CompileShaders(ReadShaderFile(vertexPath), ReadShaderFile(fragmentPath));
}

std::string Shader::ReadShaderFile(const char* path)
{
    std::string shader;
    std::ifstream file;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);

        std::stringstream stream;
        stream << file.rdbuf();
        shader = stream.str();

        file.close();
    }
    catch (std::ifstream::failure exception)
    {
        std::cout << "[ERROR]: Reading shader file failed!" << std::endl;
    }

    return shader;
}

void Shader::CompileShaders(std::string vertexCode, std::string fragmentCode)
{
    const char* vs = vertexCode.c_str();
    const char* fs = fragmentCode.c_str();

    unsigned int vertex;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vs, nullptr);
    glCompileShader(vertex);

    int vertexSuccess;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexSuccess);
    if (!vertexSuccess)
    {
        char log[512];
        glGetShaderInfoLog(vertex, 512, nullptr, log);
        std::cout << "[ERROR]: Vertex shader compilation failed!\n" << log << std::endl;
    }

    unsigned int fragment;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fs, nullptr);
    glCompileShader(fragment);

    int fragmentSuccess;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragmentSuccess);
    if (!fragmentSuccess)
    {
        char log[512];
        glGetShaderInfoLog(fragment, 512, nullptr, log);
        std::cout << "[ERROR]: Fragment shader compilation failed!\n" << log << std::endl;
    }

    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    glLinkProgram(id_);

    int linkingSuccess;
    glGetProgramiv(id_, GL_LINK_STATUS, &linkingSuccess);
    if (!linkingSuccess)
    {
        char log[512];
        glGetProgramInfoLog(id_, 512, nullptr, log);
        std::cout << "[ERROR]: Shader program linking failed!\n" << log << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
