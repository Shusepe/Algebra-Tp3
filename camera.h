#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

using namespace glm;

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    // camera Attributes
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float Zoom;

    Camera();

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : 
        Front(vec3(100.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), Zoom(ZOOM)
    {
        Position = vec3(posX, posY, posZ);
        WorldUp = vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    void LookAt()
    {
        gluLookAt(-40, 10, 0, Position.x, Position.y, Position.z, 0, 1, 0);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
      
        if (direction == Camera_Movement::FORWARD) {Position += vec3(0.0f, 1.0f, 0.0f);}

        if (direction == Camera_Movement::BACKWARD) {Position -= vec3(0.0f, 1.0f, 0.0f);}

        if (direction == Camera_Movement::LEFT) {Position -= vec3(0.0f, 0.0f, 1.0f);}
       
        if (direction == Camera_Movement::RIGHT) {Position += vec3(0.0f, 0.0f, 1.0f);}
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        vec3 front;
        front.x = cos(radians(Yaw)) * cos(radians(Pitch));
        front.y = sin(radians(Pitch));
        front.z = sin(radians(Yaw)) * cos(radians(Pitch));
        Front = normalize(front);
        // also re-calculate the Right and Up vector
        Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = normalize(cross(Right, Front));
    }
};

Camera::Camera()
{
    Position = vec3(0.0f, 0.0f, 0.0f);
    WorldUp = vec3(0.0f, 0.0f, 0.0f);
    Yaw = 0.0f;
    Pitch = 0.0f;

    Front = vec3(0.0f, 0.0f, -1.0f);
    MovementSpeed = 1.0f;
    Zoom = 1.0f;

    updateCameraVectors();
}