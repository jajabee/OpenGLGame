#pragma once

#include <glad/glad.h>

#include <string>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);

    void SetBool(const std::string& name, bool value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetInt(const std::string& name, int value) const;
    void Use();

    inline unsigned int id() const { return id_; }

private:
    void CreateShader(const char* vertexPath, const char* fragmentPath);
    std::string ReadShaderFile(const char* path);
    void CompileShaders(std::string vertexCode, std::string fragmentCode);

    unsigned int id_;
};