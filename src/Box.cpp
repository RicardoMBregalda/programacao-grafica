#include "Box.h"
#include "Cube.h"
#include <glm/gtc/matrix_transform.hpp>
Box::Box(glm::vec3 pos, float ang, Texture* glassTexture, Texture* tileTexture)
    : Object(pos, glm::vec3(0.0f), glm::vec3(1.0f), ang), glassTexture(glassTexture), tileTexture(tileTexture) {
    init();
}
void Box::init() {
    leftWall = nullptr;
    
    rightWall = new Cube(
        glm::vec3(0.4f, 0.9f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.05f, 1.8f, 1.0f),
        0.0f,
        glassTexture
    );
    
    door = new Cube(
        glm::vec3(0.0f, 0.9f, -0.5f),
        glm::vec3(0.0f),
        glm::vec3(0.8f, 1.8f, 0.05f),
        0.0f,
        glassTexture
    );
    
    floor = new Cube(
        glm::vec3(0.0f, 0.05f, 0.0f),
        glm::vec3(0.0f),
        glm::vec3(0.8f, 0.1f, 1.0f),
        0.0f,
        tileTexture
    );
}
void Box::draw(Shader& shader, glm::mat4 parentTransform) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    glm::mat4 currentTransform = parentTransform * model;
    if (leftWall) leftWall->draw(shader, currentTransform);
    if (rightWall) rightWall->draw(shader, currentTransform);
    if (door) door->draw(shader, currentTransform);
    if (floor) floor->draw(shader, currentTransform);
}
Box::~Box() {
    if (leftWall) delete leftWall;
    if (rightWall) delete rightWall;
    if (door) delete door;
    if (floor) delete floor;
}
