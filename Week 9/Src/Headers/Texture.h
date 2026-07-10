#pragma once

#include <string>

#include <glew.h>

class Texture
{
public:

    GLuint ID;

    Texture(const char* path);

    ~Texture();

    void Bind(GLuint unit = 0) const;

    void Unbind() const;

private:

    int width;
    int height;
    int channels;
};