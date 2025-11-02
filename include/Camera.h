#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    // Atributos da c�mera
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // �ngulos de Euler
    float yaw;
    float pitch;

    // Op��es da c�mera
    float sensitivity;
    float movementSpeed;
    float fov;

    // Atualiza os vetores da c�mera
    void updateCameraVectors();

public:
    // Construtor
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 8.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0f,
           float pitch = 0.0f);

    // Retorna a matriz de view
    glm::mat4 getViewMatrix() const;

    // Retorna a matriz de proje��o
    glm::mat4 getProjectionMatrix(float aspectRatio, float near = 0.1f, float far = 100.0f) const;

    // Processa input de teclado
    void processKeyboard(int direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void resetCameraPosition();
    // Processa rota��o da c�mera
    void rotate(float xOffset, float yOffset);

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    float getFOV() const;

    // Setters
    void setPosition(const glm::vec3& pos);
    void setSensitivity(float sens);
    void setMovementSpeed(float speed);
    void setFOV(float newFov);

    // Dire��es para movimento
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
