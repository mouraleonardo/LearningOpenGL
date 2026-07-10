#pragma once

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = ReadFile(vertexPath);
    std::string fragmentCode = ReadFile(fragmentPath);

    GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentCode);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID);

    CheckProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

std::string Shader::ReadFile(const char* path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "Erro ao abrir: " << path << std::endl;
        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();

    file.close();

    return stream.str();
}

GLuint Shader::Compile(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);

    const char* code = source.c_str();

    glShaderSource(shader, 1, &code, nullptr);

    glCompileShader(shader);

    GLint success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];

        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        std::cout << "Erro ao compilar Shader:\n";
        std::cout << infoLog << std::endl;
    }

    return shader;
}

void Shader::CheckProgram(GLuint program)
{
    GLint success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];

        glGetProgramInfoLog(program, 512, nullptr, infoLog);

        std::cout << "Erro ao linkar Shader Program:\n";
        std::cout << infoLog << std::endl;
    }
}

void Shader::Use() const
{
    glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        &value[0]
    );
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        &value[0][0]
    );
}