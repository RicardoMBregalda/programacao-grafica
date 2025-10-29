#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch),
      sensitivity(0.10f), movementSpeed(2.5f), fov(45.0f)
{
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    // Calcula o novo vetor front
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    // Recalcula os vetores right e up
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio, float near, float far) const {
    return glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void Camera::processKeyboard(int direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    switch(direction) {
        case FORWARD:
            position += front * velocity;
            break;
        case BACKWARD:
            position -= front * velocity;
            break;
        case LEFT:
            position -= right * velocity;
            break;
        case RIGHT:
            position += right * velocity;
            break;
        case UP:
            position += up * velocity;
            break;
        case DOWN:
            position -= up * velocity;
            break;
    }
}

void Camera::rotate(float xOffset, float yOffset) {
    yaw += xOffset * sensitivity;
    pitch += yOffset * sensitivity;

    // Limita o pitch para evitar inversão da câmera
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

// Implementação dos Getters
glm::vec3 Camera::getPosition() const {
    return position;
}

glm::vec3 Camera::getFront() const {
    return front;
}

glm::vec3 Camera::getUp() const {
    return up;
}

float Camera::getFOV() const {
    return fov;
}

// Implementação dos Setters
void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Camera::setSensitivity(float sens) {
    sensitivity = sens;
}

void Camera::setMovementSpeed(float speed) {
    movementSpeed = speed;
}

void Camera::setFOV(float newFov) {
    fov = newFov;
}
