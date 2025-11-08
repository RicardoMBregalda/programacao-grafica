#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Shader.h>
#include <Application.h>
#include <Cube.h>
#include <Banrisul.h>
#include <Texture.h>
#include <TextureManager.h>
#include <prisma.h>
#include <iostream>
#include <memory>
#include <Cilindro.h>
#include <Esfera.h>
#include <Camera.h>
#include <Chair.h>
#include <Table.h>
#include "TV.h"
#include "Bed.h"
#include "Nightstand.h"
#include "Rack.h"
#include "Lamp.h"
#include "Banqueta.h"
#include "Wardrobe.h"
#include "Wall.h"
#include "Floor.h"
#include "Sofa.h"
#include "Sala.h"
#include "Quarto.h"
#include "Porta.h"
#include "Banheiro.h"
Camera* globalCamera = nullptr;
bool firstMouse = true;
float lastX = 512.0f; 
float lastY = 384.0f; 
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    if (globalCamera != nullptr) {
        globalCamera->processMouseMovement(xoffset, yoffset);
    }
}
void verifyKeyPress(Camera& camera, Application& app, float deltaTime) {
    if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(app.getWindow(), true);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera::FORWARD, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(Camera::BACKWARD, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(Camera::LEFT, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(Camera::RIGHT, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(Camera::UP, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(Camera::DOWN, deltaTime);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_BACKSPACE) == GLFW_PRESS)
        camera.resetCameraPosition();
    if (glfwGetKey(app.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        camera.rotate(0.0f, 1.0f);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.rotate(0.0f, -1.0f);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.rotate(-1.0f, 0.0f);
    if (glfwGetKey(app.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.rotate(1.0f, 0.0f);
}
int main() {
    Application app(1024, 768, "Casa 3D Matheus e Ricardo");
    if (!app.init()) return -1;
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    std::vector<std::unique_ptr<Object>> sceneObjects;
    auto sala = std::make_unique<Sala>(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    sceneObjects.push_back(std::move(sala));
    auto portaQuarto = std::make_unique<Porta>(glm::vec3(5.0f, 0.0f, 0.0f), 270.0f);
    sceneObjects.push_back(std::move(portaQuarto));
    auto quarto = std::make_unique<Quarto>(glm::vec3(7.0f, 0.0f, -1.5f), 0.0f);
    sceneObjects.push_back(std::move(quarto));
    auto portaBanheiro = std::make_unique<Porta>(glm::vec3(-5.0f, 0.0f, -1.0f), 270.0f);
    sceneObjects.push_back(std::move(portaBanheiro));
    auto banheiro = std::make_unique<Banheiro>(glm::vec3(-6.51f, 0.0f, -1.5f), 0.0f);
    sceneObjects.push_back(std::move(banheiro));
    
    auto portaEntrada = std::make_unique<Porta>(glm::vec3(0.0f, 0.0f, 1.5f), 180.0f);
    sceneObjects.push_back(std::move(portaEntrada));
    Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));
    globalCamera = &camera;
    float deltaTime = 0.0f, lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(app.getWindow(), mouse_callback);
    while (!glfwWindowShouldClose(app.getWindow())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        verifyKeyPress(camera, app, deltaTime);
        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(1024.0f / 768.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        for (auto& obj : sceneObjects) {
            obj->draw(shader, model);
        }
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }
    return 0;
}
