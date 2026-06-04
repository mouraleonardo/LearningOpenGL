/*
    ============================================================
    Renderer.cpp

    Purpose:
    Handles all drawing and animation for the scene.

    This class is responsible for:
        • Sending shader data to the GPU
        • Building transformation matrices
        • Moving the car across the screen
        • Rotating the wheel rims
        • Scaling and translating smoke particles
        • Drawing all meshes in the correct positions

    Transformations Demonstrated:
        • Translation
        • Rotation
        • Scaling

    Matrix Pipeline:
        MVP = Projection × View × Model

        Projection -> Defines visible world area
        View       -> Camera transformation
        Model      -> Object transformation

    ============================================================
*/

#include "Renderer.h"

// OpenGL functions
#include <glew.h>

// GLM mathematics library
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Mathematical functions such as fmod()
#include <cmath>

/*
    Constructor

    Stores pointers to the shader and meshes
    so they can be used during rendering.
*/
Renderer::Renderer(
    Shader* shader,
    Mesh* bodyMesh,
    Mesh* wheelMesh,
    Mesh* starMesh,
    Mesh* smokeMesh)
{
    this->shader = shader;

    this->bodyMesh = bodyMesh;
    this->wheelMesh = wheelMesh;
    this->starMesh = starMesh;
    this->smokeMesh = smokeMesh;
}

/*
    Render()

    Called once every frame.

    Parameter:
        time = elapsed time since program started

    Uses time to animate:
        • Car movement
        • Wheel rotation
        • Smoke movement
*/
void Renderer::Render(float time)
{
    //----------------------------------------------------
    // Activate shader program
    //----------------------------------------------------

    shader->Use();

    //----------------------------------------------------
    // Send current time to shader
    //----------------------------------------------------

    GLint timeLocation =
        glGetUniformLocation(
            shader->GetID(),
            "time");

    glUniform1f(
        timeLocation,
        time);

    //----------------------------------------------------
    // Get location of MVP matrix uniform
    //----------------------------------------------------

    GLint mvpLocation =
        glGetUniformLocation(
            shader->GetID(),
            "mvp");

    /*
        =================================================
        PROJECTION MATRIX
        =================================================

        Creates an orthographic projection.

        Visible area:

            x = -5 to +5
            y = -3 to +3

        No perspective distortion.
    */

    glm::mat4 projection =
        glm::ortho(
            -5.0f,
            5.0f,
            -3.0f,
            3.0f,
            -1.0f,
            1.0f);

    /*
        =================================================
        VIEW MATRIX
        =================================================

        Identity matrix means:

            No camera movement
            No camera rotation

        Camera remains at origin.
    */

    glm::mat4 view =
        glm::mat4(1.0f);

    /*
        =================================================
        CAR ANIMATION VALUES
        =================================================
    */

    // Keeps time repeating every 10 seconds
    float cycleTime =
        fmod(time, 10.0f);

    /*
        Moves car from:

            x = -6
            to
            x = +6

        over 10 seconds.
    */
    float carX =
        -6.0f +
        (cycleTime / 10.0f) * 12.0f;

    /*
        Wheel rotation angle.

        Negative value causes clockwise rotation.
    */
    float wheelAngle =
        -time * 6.0f;

    /*
        =================================================
        CAR BODY
        =================================================

        Translation transformation.

        Moves entire body horizontally.
    */

    glm::mat4 modelBody =
        glm::translate(
            glm::mat4(1.0f),
            glm::vec3(
                carX,
                0.0f,
                0.0f));

    /*
        Final transformation matrix:

        MVP = Projection × View × Model
    */
    glm::mat4 mvpBody =
        projection *
        view *
        modelBody;

    // Send matrix to shader
    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(mvpBody));

    // Draw car body
    bodyMesh->Draw();

    /*
        =================================================
        REAR WHEEL
        =================================================
    */

    /*
        Position wheel relative to car.

        Since car moves, wheel must move too.
    */
    glm::vec3 rearWheelPosition(
        carX - 1.55f,
        -0.65f,
        0.0f);

    /*
        Translation matrix
    */
    glm::mat4 rearWheelModel =
        glm::translate(
            glm::mat4(1.0f),
            rearWheelPosition);

    glm::mat4 rearWheelMVP =
        projection *
        view *
        rearWheelModel;

    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(rearWheelMVP));

    // Draw tire
    wheelMesh->Draw();

    /*
        =================================================
        REAR STAR (RIM)
        =================================================

        Demonstrates rotation.
    */

    glm::mat4 rearStarModel =
        glm::translate(
            glm::mat4(1.0f),
            rearWheelPosition);

    /*
        Rotate around Z-axis.

        Since translation occurs first,
        rotation happens around wheel center.
    */
    rearStarModel =
        glm::rotate(
            rearStarModel,
            wheelAngle,
            glm::vec3(
                0.0f,
                0.0f,
                1.0f));

    glm::mat4 rearStarMVP =
        projection *
        view *
        rearStarModel;

    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(rearStarMVP));

    // Draw spinning rim
    starMesh->Draw();

    /*
        =================================================
        FRONT WHEEL
        =================================================
    */

    glm::vec3 frontWheelPosition(
        carX + 1.55f,
        -0.65f,
        0.0f);

    glm::mat4 frontWheelModel =
        glm::translate(
            glm::mat4(1.0f),
            frontWheelPosition);

    glm::mat4 frontWheelMVP =
        projection *
        view *
        frontWheelModel;

    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(frontWheelMVP));

    // Draw tire
    wheelMesh->Draw();

    /*
        =================================================
        FRONT STAR (RIM)
        =================================================
    */

    glm::mat4 frontStarModel =
        glm::translate(
            glm::mat4(1.0f),
            frontWheelPosition);

    /*
        Rotate rim continuously
    */
    frontStarModel =
        glm::rotate(
            frontStarModel,
            wheelAngle,
            glm::vec3(
                0.0f,
                0.0f,
                1.0f));

    glm::mat4 frontStarMVP =
        projection *
        view *
        frontStarModel;

    glUniformMatrix4fv(
        mvpLocation,
        1,
        GL_FALSE,
        glm::value_ptr(frontStarMVP));

    // Draw spinning rim
    starMesh->Draw();

    /*
        =================================================
        SMOKE ANIMATION
        =================================================

        Demonstrates BOTH translation and scaling.

        Creates 3 smoke puffs that:

            • Move left
            • Move upward
            • Grow larger

        The loop creates multiple smoke particles
        using the same mesh.
    */

    for (int i = 0; i < 3; i++)
    {
        /*
            Creates different positions in
            the animation cycle for each puff.
        */
        float offset =
            fmod(
                time * 0.8f +
                i * 1.0f,
                3.0f);

        /*
            Smoke grows as it moves away
            from the exhaust pipe.
        */
        float scale =
            0.3f +
            offset * 0.3f;

        /*
            Translation:

            Moves smoke left and upward.
        */
        glm::mat4 smokeModel =
            glm::translate(
                glm::mat4(1.0f),
                glm::vec3(
                    carX - 2.88f - offset,
                    -0.45f + offset * 0.08f,
                    0.0f));

        /*
            Scaling:

            Makes smoke expand over time.
        */
        smokeModel =
            glm::scale(
                smokeModel,
                glm::vec3(
                    scale,
                    scale,
                    1.0f));

        glm::mat4 smokeMVP =
            projection *
            view *
            smokeModel;

        glUniformMatrix4fv(
            mvpLocation,
            1,
            GL_FALSE,
            glm::value_ptr(smokeMVP));

        // Draw smoke particle
        smokeMesh->Draw();
    }
}