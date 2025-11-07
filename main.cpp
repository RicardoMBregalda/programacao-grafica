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
#include "Sofa.h"
#include "Sala.h"
#include "Quarto.h"
#include "Porta.h"

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

void verifyKeyPress(Camera& camera, Application& app, float deltaTime) {
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
}


void createScene(std::vector<std::unique_ptr<Object>>& sceneObjects, 
                 Texture* woodTex, Texture* metalTex, Texture* plasticTex, Texture* blackTex, 
                 Texture* fabricTex, Texture* fabricTex2, Texture* stoneTex) {
    
    // Cria a sala completa com todos os móveis organizados
    auto sala = std::make_unique<Sala>(
        glm::vec3(0.0f, 0.0f, 0.0f),  // Posição central
        0.0f,                          // Sem rotação
        woodTex,                       // Textura de madeira
        metalTex,                      // Textura de metal
        plasticTex,                    // Textura de plástico
        blackTex,                      // Textura preta
        fabricTex,                     // Textura de tecido (sofá)
        fabricTex2,                    // Textura de tecido 2 (tapete)
        stoneTex                       // Textura de pedra/tijolo
    );
    sceneObjects.push_back(std::move(sala));

    // Porta de conexão entre sala e quarto
    auto porta = std::make_unique<Porta>(
        glm::vec3(5.0f, 0.0f, 0.0f),   // Posição entre sala e quarto
        270.0f,                          // Rotação de 90° para ficar perpendicular
        woodTex,                        // Textura de madeira para porta e batente
        metalTex                        // Textura de metal para maçanetas
    );
    sceneObjects.push_back(std::move(porta));

    auto quarto = std::make_unique<Quarto>(
        glm::vec3(7.0f, 0.0f, -1.5f),
        0.0f,
        woodTex,     // madeira (cama, criado, guarda-roupa, piso)
        fabricTex,   // tecido para colchão
        fabricTex2,  // tecido para travesseiros
        metalTex,    // metal (puxadores, base da luminária)
        blackTex,    // bulb (lâmpada)
        stoneTex     // wall (paredes)
    );
    sceneObjects.push_back(std::move(quarto));
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
    Texture texMadeira("madeira.jpg");
    Texture texMetal("metal.png");
    Texture texPlastico("plastico.jpg");  
    Texture texBlack("black.jpg");
    Texture texTecido("tecido.jpg");       // Textura de tecido para colchão
    Texture texTecido2("tecido_claro.jpg");      // Textura de tecido para travesseiros (pode ser a mesma ou diferente)

    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // Cria cena (passando todas as texturas)
    std::vector<std::unique_ptr<Object>> sceneObjects;
    createScene(sceneObjects, &texMadeira, &texMetal, &texPlastico, &texBlack, &texTecido, &texTecido2, &tex1);

    // Camera - posicionada para ver toda a sala
    Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));
    
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

        verifyKeyPress(camera, app, deltaTime);

        glClearColor(0.7f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(1024.0f / 768.0f);

        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // Texturas
        tex1.bind(0);

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
