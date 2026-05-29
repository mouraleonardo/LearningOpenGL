#include "Renderer.h"

#include <glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/*
    Constructor

    Receives pointers to the Shader and Mesh
    objects that will be used during rendering.

    The renderer is responsible for applying
    transformations and drawing the mesh.
*/
Renderer::Renderer(
    Shader* shader,
    Mesh* mesh)
{
    this->shader = shader;
    this->mesh = mesh;
}

/*
    Render Function

    Renders the mesh using the specified shader.

    The rendering process consists of:

    1. Activating the shader program.
    2. Creating the Model matrix.
    3. Creating the View matrix.
    4. Creating the Projection matrix.
    5. Combining them into a single MVP matrix.
    6. Sending the MVP matrix to the GPU.
    7. Drawing the mesh.

    angle:
        Rotation angle in radians used to
        continuously rotate the cube around
        the Y axis.
*/
void Renderer::Render(float angle)
{
    // Activate the shader program
    shader->Use();

    /*
        Model Matrix

        Defines the object's transformation
        in world space.

        In this project, the cube rotates
        continuously around the Y axis.
    */
    glm::mat4 model =
        glm::rotate(
            glm::mat4(1.0f),
            angle,
            glm::vec3(0.0f, 1.0f, 0.0f));

    /*
        View Matrix

        Represents the camera position.

        Moving the scene backward along
        the Z axis creates the effect of
        a camera positioned away from
        the object.
    */
    glm::mat4 view =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(0.0f, 0.0f, -3.0f));

    /*
        Projection Matrix

        Creates perspective projection.

        Parameters:

        45.0f       = Field of View (FOV)
        800 / 600   = Aspect Ratio
        0.1f        = Near Clipping Plane
        100.0f      = Far Clipping Plane

        Perspective projection makes
        distant objects appear smaller,
        creating the illusion of depth.
    */
    glm::mat4 projection =
        glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f);

    /*
        MVP Matrix

        Combines all transformations into
        a single matrix.

        MVP = Projection × View × Model

        This matrix transforms vertices
        from local object space to clip space.
    */
    glm::mat4 mvp =
        projection *
        view *
        model;

    /*
        Retrieve the location of the
        MVP uniform variable inside
        the shader program.
    */
    GLint mvpLocation =
        glGetUniformLocation(
            shader->GetID(),
            "mvp");

    /*
        Send the MVP matrix to the GPU.

        The vertex shader uses this matrix
        to transform each vertex before
        rasterization.
    */
    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(mvp));

    /*
        Draw the mesh using the configured
        shader and transformation matrices.
    */
    mesh->Draw();
}