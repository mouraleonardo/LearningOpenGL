#pragma once

#include <string>

#include <glew.h>
#include <glm.hpp>


class Shader
{
public:

    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void Use() const;

    void SetBool(const std::string& name, bool value) const;

    void SetInt(const std::string& name, int value) const;

    void SetFloat(const std::string& name, float value) const;

    void SetVec3(const std::string& name, const glm::vec3& value) const;

    void SetMat4(const std::string& name, const glm::mat4& value) const;

private:

    std::string ReadFile(const char* path);

    GLuint Compile(GLenum type, const std::string& source);

    void CheckProgram(GLuint program);
};