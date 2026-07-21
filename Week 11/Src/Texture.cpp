/*
    ============================================================
    Texture - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This file implements the Texture class.

    The implementation is responsible for loading image files
    using the stb_image library and creating an OpenGL texture
    object that can be used during rendering.

    The loading process includes:

        • Creating the OpenGL texture object
        • Loading image data from disk
        • Detecting the image format
        • Uploading pixels to GPU memory
        • Configuring wrapping parameters
        • Configuring filtering parameters
        • Generating mipmaps
        • Releasing CPU image memory

    Technologies:

        • OpenGL 3.3 Core Profile
        • stb_image
        • GLEW
        • C++

    Learning Topics:

        • Texture Creation
        • Image Loading
        • Texture Parameters
        • GPU Memory Upload
        • Mipmap Generation
        • Resource Management

    ============================================================
*/

#include "Texture.h"

#include <iostream>

// stb_image implementation.
// This macro must appear in exactly one source file.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path)
{
    //---------------------------------------------------------
    // Create a new OpenGL texture object.
    //---------------------------------------------------------

    glGenTextures(1, &ID);

    //---------------------------------------------------------
    // Bind the texture so it becomes the active texture.
    //---------------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, ID);

    //---------------------------------------------------------
    // Configure texture wrapping.
    //
    // GL_REPEAT repeats the texture whenever UV coordinates
    // exceed the [0,1] range.
    //---------------------------------------------------------

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    //---------------------------------------------------------
    // Configure texture filtering.
    //
    // MIN_FILTER is used when the texture becomes smaller.
    // MAG_FILTER is used when the texture becomes larger.
    //---------------------------------------------------------

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    //---------------------------------------------------------
    // Flip the image vertically.
    //
    // stb_image loads images with the origin at the top-left.
    // OpenGL expects the origin at the bottom-left.
    //---------------------------------------------------------

    stbi_set_flip_vertically_on_load(true);

    //---------------------------------------------------------
    // Load the image from disk.
    //---------------------------------------------------------

    unsigned char* data = stbi_load(
        path,
        &width,
        &height,
        &channels,
        0
    );

    //---------------------------------------------------------
    // Verify that the image was loaded successfully.
    //---------------------------------------------------------

    if (data)
    {
        //-----------------------------------------------------
        // Determine the correct OpenGL texture format.
        //-----------------------------------------------------

        GLenum format = GL_RGB;

        if (channels == 1)
            format = GL_RED;

        else if (channels == 3)
            format = GL_RGB;

        else if (channels == 4)
            format = GL_RGBA;

        //-----------------------------------------------------
        // Upload the image to GPU memory.
        //-----------------------------------------------------

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

        //-----------------------------------------------------
        // Generate mipmaps automatically.
        //-----------------------------------------------------

        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout
            << "Texture loaded successfully: "
            << path
            << std::endl;
    }
    else
    {
        //-----------------------------------------------------
        // Image loading failed.
        //-----------------------------------------------------

        std::cout
            << "Failed to load texture: "
            << path
            << std::endl;
    }

    //---------------------------------------------------------
    // Release CPU memory allocated by stb_image.
    //---------------------------------------------------------

    stbi_image_free(data);

    //---------------------------------------------------------
    // Unbind the texture.
    //---------------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    //---------------------------------------------------------
    // Release the texture stored in GPU memory.
    //---------------------------------------------------------

    glDeleteTextures(1, &ID);
}

void Texture::Bind(GLuint unit) const
{
    //---------------------------------------------------------
    // Activate the desired texture unit.
    //---------------------------------------------------------

    glActiveTexture(GL_TEXTURE0 + unit);

    //---------------------------------------------------------
    // Bind this texture to the active texture unit.
    //---------------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
    //---------------------------------------------------------
    // Unbind the current texture.
    //---------------------------------------------------------

    glBindTexture(GL_TEXTURE_2D, 0);
}