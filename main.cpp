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
#include "Sink.h"






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

    // Objetos de cena
    Prisma prisma(glm::vec3(4.0f, 0.0f, 0.0f));
    Cube cube1(glm::vec3(2.0f, 0.0f, -2.5f));
    Cube cube2(glm::vec3(-2.0f, 1.0f, -4.0f));
    Cube cube3(glm::vec3(-3.0f, -1.0f, 3.0f));

    Banrisul banri(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
    banri.scale = glm::vec3(2.5f);

    Chair chair(glm::vec3(-1.0f, 0.0f, 2.0f), 0.0f);
    chair.scale = glm::vec3(1.5f);


    Bed bed(glm::vec3(0.0f, 0.0f, -3.0f), 0.0f);
    bed.scale = glm::vec3(1.0f);

    Nightstand nightstand(glm::vec3(-1.5f, 0.0f, -3.0f), 0.0f);


    Table table(glm::vec3(0.0f, 0.0f, -1.5f), 0.0f);
    table.scale = glm::vec3(1.2f, 1.2f, 1.2f);


    Cilindro cilindro(glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(1.0f, 0.0f, 0.0f),
                      glm::vec3(1.0f, 2.0f, 1.0f),
                      45.0f, 36);

    Esfera esfera(glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f),
                  glm::vec3(1.0f),
                  0.0f,
                  18, 36);

    // Criar o rack
    Rack rack(glm::vec3(0.0f, 0.0f, -4.0f), 0.0f);

    // Criar a TV em cima do rack
    TV tv(glm::vec3(0.0f, 0.38f, -4.0f), 0.0f);

    // Lamp posicionada no criado-mudo
    Lamp lamp(glm::vec3(-1.5f, 0.55f, -3.0f), 0.0f);
    lamp.scale = glm::vec3(0.8f);

    Banqueta banqueta(glm::vec3(1.5f, 0.0f, -2.0f), 0.0f);
    banqueta.scale = glm::vec3(1.0f);


    Sink sink(glm::vec3(2.0f, 0.0f, -1.0f), 0.0f);


    Wardrobe wardrobe(glm::vec3(3.0f, 0.0f, -3.0f), 0.0f);


    Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));

    float deltaTime = 0.0f, lastFrame = 0.0f;
    glEnable(GL_DEPTH_TEST);

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

        // Teste simples: desenhar um cubo primeiro
        //nightstand.draw(shader, model);
        //esfera.draw(shader, glm::mat4(1.0f));
        //table.draw(shader, glm::mat4(1.0f));
        //bed.draw(shader, model);
        //chair.draw(shader, model);
        // banri.draw(shader, model);
        // cilindro.draw(shader, glm::mat4(1.0f));
        //rack.draw(shader, model);
        //tv.draw(shader, model);
        //lamp.draw(shader, model);
        //banqueta.draw(shader, model);
        //wardrobe.draw(shader, model);

        sink.draw(shader, model);

        glfwSwapBuffers(app.getWindow());
        glfwPollEvents();
    }

    return 0;
}
