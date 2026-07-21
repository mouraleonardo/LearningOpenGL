/*
    ============================================================
    FPS Camera - OpenGL

    Author: Leonardo Moura
    Date: 2026

    Description:

    This class implements a simple First-Person Camera (FPS)
    used to navigate a 3D environment.

    The camera stores its position, orientation, movement
    parameters, and generates the View Matrix required by the
    OpenGL rendering pipeline.

    Camera orientation is controlled using Euler Angles
    (Yaw and Pitch), while movement is performed relative to
    the camera's local coordinate system.

    The class supports:

        • Forward and backward movement
        • Left and right strafing
        • Mouse Look
        • Mouse Wheel Zoom
        • Frame-independent movement
        • Automatic View Matrix generation

    Technologies:

        • OpenGL 3.3 Core Profile
        • GLM
        • C++

    Learning Topics:

        • Camera Systems
        • View Matrix
        • Euler Angles
        • Local Coordinate System
        • Direction Vectors
        • Cross Product
        • Normalization
        • FPS Navigation

    ============================================================
*/

#pragma once

#include <glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

//
// Defines the possible camera movement directions.
//
enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:

    //----------------------------------------------------------
    // Camera position in World Space.
    //----------------------------------------------------------
    glm::vec3 Position;

    //----------------------------------------------------------
    // Forward direction.
    //
    // Indicates where the camera is looking.
    //----------------------------------------------------------
    glm::vec3 Front;

    //----------------------------------------------------------
    // Up direction.
    //
    // Represents the camera's vertical axis.
    //----------------------------------------------------------
    glm::vec3 Up;

    //----------------------------------------------------------
    // Right direction.
    //
    // Represents the camera's horizontal axis.
    //----------------------------------------------------------
    glm::vec3 Right;

    //----------------------------------------------------------
    // World's Up vector.
    //
    // Usually (0, 1, 0).
    //----------------------------------------------------------
    glm::vec3 WorldUp;

    //----------------------------------------------------------
    // Horizontal rotation.
    //
    // Measured in degrees.
    //----------------------------------------------------------
    float Yaw;

    //----------------------------------------------------------
    // Vertical rotation.
    //
    // Measured in degrees.
    //----------------------------------------------------------
    float Pitch;

    //----------------------------------------------------------
    // Camera movement speed.
    //----------------------------------------------------------
    float MovementSpeed;

    //----------------------------------------------------------
    // Mouse sensitivity.
    //
    // Controls how fast the camera rotates.
    //----------------------------------------------------------
    float MouseSensitivity;

    //----------------------------------------------------------
    // Camera field of view.
    //
    // Used when generating the Perspective Projection Matrix.
    //----------------------------------------------------------
    float Zoom;

    //----------------------------------------------------------
    // Constructor.
    //
    // Creates a camera with an initial position and
    // orientation.
    //----------------------------------------------------------
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 1.5f, 5.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f
    );

    //----------------------------------------------------------
    // Returns the View Matrix.
    //
    // The View Matrix transforms objects from World Space
    // into Camera (View) Space.
    //----------------------------------------------------------
    glm::mat4 GetViewMatrix();

    //----------------------------------------------------------
    // Processes keyboard movement.
    //
    // Movement is relative to the camera orientation and uses
    // delta time for frame-independent motion.
    //----------------------------------------------------------
    void ProcessKeyboard(
        CameraMovement direction,
        float deltaTime
    );

    //----------------------------------------------------------
    // Updates the camera orientation using mouse movement.
    //
    // Mouse movement modifies the Yaw and Pitch angles.
    //----------------------------------------------------------
    void ProcessMouseMovement(
        float xoffset,
        float yoffset
    );

    //----------------------------------------------------------
    // Updates the camera zoom using the mouse wheel.
    //----------------------------------------------------------
    void ProcessMouseScroll(
        float yoffset
    );

private:

    //----------------------------------------------------------
    // Recalculates the camera coordinate system.
    //
    // This function updates the Front, Right, and Up vectors
    // after the camera orientation changes.
    //----------------------------------------------------------
    void UpdateCameraVectors();
};