/*
    ============================================================
    Fragment Shader
    File: fragment.glsl

    Author: Leonardo Moura
    Date: 6/4/2026

    Purpose:
    This shader determines the final color of every pixel
    (fragment) drawn on the screen.

    After the vertex shader processes the vertices and the
    rasterizer generates fragments between those vertices,
    this shader calculates the color that will appear on
    the screen.

    Concepts Demonstrated:
        • Fragment Processing
        • Color Manipulation
        • Gradient Effects
        • Animation Using Time
        • Conditional Rendering
        • Interpolated Vertex Data

    Inputs From Vertex Shader:

        vertexColor
            Original color assigned to the vertex.

            OpenGL automatically interpolates this color
            across the surface of each triangle.

        vertexHeight
            Original Y-coordinate of the vertex.

            Interpolated across the triangle and used to
            create a vertical lighting gradient.

        worldX
            Original X-coordinate of the vertex.

            Interpolated across the triangle and used to
            create an animated reflection effect.

    Uniforms:

        time
            Current elapsed time in seconds.

            Sent from the CPU each frame and used to
            animate visual effects.

    Output:

        FragColor
            Final RGBA color of the current fragment.

            R = Red
            G = Green
            B = Blue
            A = Alpha (Transparency)

    Visual Effects Implemented:

    1. Body Gradient

        Creates a simple lighting effect by making
        higher areas of the car slightly brighter.

        Lower portions:
            Darker

        Upper portions:
            Brighter

        This gives the car body a more three-dimensional
        appearance without using real lighting.

    2. Window Reflection

        Detects window pixels by checking for the
        blue window color.

        Applies an animated shine effect using a
        sine wave.

        The reflection moves horizontally across
        the windows over time.

    Animation Formula:

        sin(worldX * 10 + time * 4)

        worldX * 10
            Controls reflection position.

        time * 4
            Controls reflection movement speed.

    Graphics Pipeline:

        Vertex Shader
             ↓
        Rasterizer
             ↓
        Fragment Shader  ← This File
             ↓
        Final Pixel Color

    Notes:

        Every visible pixel of every object executes
        this shader.

        The shader does not move geometry.

        It only changes the appearance and color of
        fragments after the geometry has already been
        positioned by the vertex shader.

    ============================================================
*/

#version 330 core

// Color received from the vertex shader
in vec3 vertexColor;

// Original Y position received from vertex shader
in float vertexHeight;

// Original X position received from vertex shader
in float worldX;

// Current elapsed time used for animation
uniform float time;

// Final pixel color sent to the framebuffer
out vec4 FragColor;

void main()
{
    // Start with the interpolated vertex color
    vec3 color = vertexColor;

    /*
        BODY GRADIENT

        Makes higher parts of the car slightly brighter.

        Produces a simple fake lighting effect.
    */
    float gradient =
        0.80 +
        ((vertexHeight + 1.0) / 3.0) * 0.20;

    color *= gradient;

    /*
        WINDOW REFLECTION

        Identify window pixels by checking
        for the blue window color.
    */
    bool isWindow =
        color.b > 0.7 &&
        color.g > 0.6;

    if (isWindow)
    {
        /*
            Animated shine effect.

            Sine wave creates a moving highlight
            across the windows.
        */
        float shine =
            max(
                0.0,
                sin(
                    worldX * 10.0 +
                    time * 4.0));

        /*
            Add brightness to the window.
        */
        color += vec3(
            shine * 0.15);
    }

    /*
        Output final pixel color.

        Alpha = 1.0 means fully opaque.
    */
    FragColor =
        vec4(
            color,
            1.0);
}