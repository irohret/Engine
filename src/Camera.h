#pragma once 


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../math/Matrix.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// typedef struct Vector3 {
//     float x, y, z;
// };

// class Camera {
// public:
//     // Constructor with default values
//     Camera() : position(Vector3{0.0f, 0.0f, 0.0f}), front(Vector3{0.0f, 0.0f, -1.0f}), up(Vector3{0.0f, 1.0f, 0.0f}),
//                yaw(YAW), pitch(PITCH), MovementSpeed(SPEED), zoom(ZOOM), MOuseSensivity(SENSITIVITY) {
//                 this->front = Vector3{0.0f, 0.0f, -1.0f};
                
//                }

//     // Destructor
//     ~Camera();

//     Vector3 position;
//     Vector3 front;
//     Vector3 up;

//     float yaw;
//     float pitch;
//     float MovementSpeed;
//     float zoom;
//     float MOuseSensivity;

//     void ProcessKeyboard(Camera_Movement direction, float deltaTime);
//     void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
// };
