#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float sensitivity;
    float movementSpeed;
    float fov;
    void updateCameraVectors();
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 8.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspectRatio, float near = 0.1f, float far = 100.0f) const;
    void processKeyboard(int direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void resetCameraPosition();
    void rotate(float xOffset, float yOffset);
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    float getFOV() const;
    void setPosition(const glm::vec3& pos);
    void setSensitivity(float sens);
    void setMovementSpeed(float speed);
    void setFOV(float newFov);
    enum Direction {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
};
#endif
