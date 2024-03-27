
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

float MovementSpeed = 2.5f;

// void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
//     float velocity = MovementSpeed * deltaTime;
    
//     if (direction == FORWARD)
//         position += Front * velocity;
//     if (direction == BACKWARD)
//         position -= Front * velocity;
//     if (direction == LEFT)
//         position -= Right * velocity;
//     if (direction == RIGHT)
//         position += Right * velocity;
// }

// void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
//     xoffset *= MOuseSensivity;
//     yoffset *= MOuseSensivity;

//     yaw += xoffset;
//     pitch += yoffset;

//     // Constrain pitch to avoid gimbal lock
//     if (constrainPitch) {
//         if (pitch > 89.0f)
//             pitch = 89.0f;
//         if (pitch < -89.0f)
//             pitch = -89.0f;
//     }

//     // Update front, right, and up vectors using updated yaw and pitch values
//     updateCameraVectors();
// }

// void Camera::updateCameraVectors() {
//     // Calculate the new Front vector
//     Vector3 newFront;
//     newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//     newFront.y = sin(glm::radians(pitch));
//     newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//     front = normalize(newFront);

//     // Recalculate Right and Up vectors
//     right = normalize(cross(front, worldUp));
//     up = normalize(cross(right, front));
// }
