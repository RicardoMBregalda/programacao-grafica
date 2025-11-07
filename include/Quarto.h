#ifndef QUARTO_H
#define QUARTO_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Floor;
class Wall;
class Bed;
class Nightstand;
class Lamp;
class Wardrobe;
class Quarto : public Object {
private:
    std::vector<std::unique_ptr<Object>> components;
    void createRoom();
    void createFurniture();
public:
    Quarto(glm::vec3 pos, float ang);
    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};
#endif 