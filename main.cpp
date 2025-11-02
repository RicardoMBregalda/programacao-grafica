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

// Variáveis globais para controle do mouse
Camera* globalCamera = nullptr;
bool firstMouse = true;
float lastX = 512.0f; 
float lastY = 384.0f; 

//peguei daqui: https://learnopengl.com/Getting-started/Camera
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (globalCamera != nullptr)
    {
        globalCamera->processMouseMovement(xoffset, yoffset);
    }
}

int main() {
    // Cria janela e inicializa OpenGL
    Application app(1024, 768, "Cena 3D - Objetos OOP");
    if (!app.init()) return -1;

    // Shader
    Shader shader("vertex.glsl", "fragment.glsl");
    shader.use();

    // Carrega texturas
    Texture tex1("pedra-28.jpg");
    Texture tex2("opengl.png");

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    std::vector<std::unique_ptr<Object>> sceneObjects;

    // Paredes e chão
    sceneObjects.push_back(std::make_unique<Wall>(glm::vec3(6.0f, 0.0f, -3.0f), 0.0f));
    sceneObjects.push_back(std::make_unique<Floor>(glm::vec3(7.0f, 0.0f, -3.0f), 0.0f));
  

    auto chair = std::make_unique<Chair>(glm::vec3(-1.0f, 0.0f, 2.0f), 0.0f);
    chair->scale = glm::vec3(1.5f);
    sceneObjects.push_back(std::move(chair));

    auto bed = std::make_unique<Bed>(glm::vec3(0.0f, 0.0f, -3.0f), 0.0f);
    bed->scale = glm::vec3(1.0f);
    sceneObjects.push_back(std::move(bed));

    sceneObjects.push_back(std::make_unique<Nightstand>(glm::vec3(-1.5f, 0.0f, -3.0f), 0.0f));

    auto table = std::make_unique<Table>(glm::vec3(0.0f, 0.0f, -1.5f), 0.0f);
    table->scale = glm::vec3(1.2f, 1.2f, 1.2f);
    sceneObjects.push_back(std::move(table));

    sceneObjects.push_back(std::make_unique<Rack>(glm::vec3(0.0f, 0.0f, -4.0f), 0.0f));

    sceneObjects.push_back(std::make_unique<TV>(glm::vec3(0.0f, 0.38f, -4.0f), 0.0f));

    auto lamp = std::make_unique<Lamp>(glm::vec3(-1.5f, 0.55f, -3.0f), 0.0f);
    lamp->scale = glm::vec3(0.8f);
    sceneObjects.push_back(std::move(lamp));

    auto banqueta = std::make_unique<Banqueta>(glm::vec3(1.5f, 0.0f, -2.0f), 0.0f);
    banqueta->scale = glm::vec3(1.0f);
    sceneObjects.push_back(std::move(banqueta));

    auto wardrobe = std::make_unique<Wardrobe>(glm::vec3(3.0f, 0.0f, -3.0f), 0.0f);
    wardrobe->scale = glm::vec3(1.2f);
    sceneObjects.push_back(std::move(wardrobe));

    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));
    
    globalCamera = &camera;

    float deltaTime = 0.0f, lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);
    
    // Configura o mouse para controlar a câmera
    glfwSetInputMode(app.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(app.getWindow(), mouse_callback);  

    // Loop principal
    while (!glfwWindowShouldClose(app.getWindow())) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (glfwGetKey(app.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(app.getWindow(), true);

        // Movimentação básica
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

        // Reseta a posição da câmera
        if(glfwGetKey(app.getWindow(), GLFW_KEY_BACKSPACE) == GLFW_PRESS)
            camera.resetCameraPosition();

        // Rotação com setas
        if (glfwGetKey(app.getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
            camera.rotate(0.0f, 1.0f);
        if (glfwGetKey(app.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
            camera.rotate(0.0f, -1.0f);
        if (glfwGetKey(app.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
            camera.rotate(-1.0f, 0.0f);
        if (glfwGetKey(app.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
            camera.rotate(1.0f, 0.0f);

        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(1024.0f / 768.0f);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Texturas
        tex1.bind(0);
        tex2.bind(1);

        glm::mat4 model = glm::mat4(1.0f);

        // Desenha objetos
        for (auto& obj : sceneObjects) {
            obj->draw(shader, model);
        }
        
        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
