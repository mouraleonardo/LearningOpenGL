#include "Texture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Configuração de repetição da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Configuração de filtragem
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // OpenGL considera a origem no canto inferior esquerdo
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(
        path,
        &width,
        &height,
        &channels,
        0
    );

    if (data)
    {
        GLenum format = GL_RGB;

        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "Textura carregada: "
            << path
            << std::endl;
    }
    else
    {
        std::cout << "Erro ao carregar textura: "
            << path
            << std::endl;
    }

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}

void Texture::Bind(GLuint unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}