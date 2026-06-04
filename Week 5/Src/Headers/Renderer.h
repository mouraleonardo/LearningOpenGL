/*
    ============================================================
    Renderer.h

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    Defines the Renderer class responsible for drawing
    and animating all objects in the scene.

    The Renderer acts as the connection between:

        • Shader Program
        • Mesh Geometry
        • Transformation Matrices
        • Animation Logic

    Responsibilities:
        • Draw the car body
        • Draw both wheels
        • Draw rotating wheel rims
        • Draw animated smoke particles
        • Apply translation, rotation, and scaling
        • Send transformation matrices to shaders

    Graphics Concepts Demonstrated:

        Translation
            Moves the car across the screen.

        Rotation
            Rotates the wheel rims while the
            vehicle moves.

        Scaling
            Expands smoke particles as they
            move away from the exhaust.

        MVP Matrix
            Model × View × Projection

            Used to transform objects from
            local coordinates into screen
            coordinates.

    Renderer Components:

        Shader
            Controls how objects are rendered.

        Body Mesh
            Geometry representing the car body.

        Wheel Mesh
            Geometry representing the tires.

        Star Mesh
            Geometry representing wheel rims.

        Smoke Mesh
            Geometry representing smoke particles.

    Main Function:

        Render(float time)

            Called once every frame.

            Uses elapsed time to animate:

                • Car movement
                • Wheel rotation
                • Smoke effects

    Rendering Pipeline:

        Mesh Data
             ↓
        Renderer
             ↓
        Shader Program
             ↓
        GPU
             ↓
        Screen

    ============================================================
*/

#ifndef RENDERER_H
#define RENDERER_H

// Shader class used for GPU rendering
#include "Shader.h"

// Mesh class containing geometry data
#include "Mesh.h"

/*
    Renderer Class

    Responsible for drawing and animating
    all scene objects.
*/
class Renderer
{
private:

    /*
        Pointer to the active shader program.

        Used to send uniforms and render objects.
    */
    Shader* shader;

    /*
        Car body geometry.
    */
    Mesh* bodyMesh;

    /*
        Wheel/tire geometry.
    */
    Mesh* wheelMesh;

    /*
        Wheel rim (star) geometry.
    */
    Mesh* starMesh;

    /*
        Smoke particle geometry.
    */
    Mesh* smokeMesh;

public:

    /*
        Constructor

        Receives pointers to all meshes and
        the shader used during rendering.
    */
    Renderer(
        Shader* shader,
        Mesh* bodyMesh,
        Mesh* wheelMesh,
        Mesh* starMesh,
        Mesh* smokeMesh);

    /*
        Render Function

        Parameter:
            time = elapsed time in seconds

        Called once per frame.

        Responsible for:

            • Updating animation
            • Building transformation matrices
            • Sending uniforms to shaders
            • Drawing all scene objects
    */
    void Render(float time);
};

#endif