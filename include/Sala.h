#ifndef SALA_H
#define SALA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Texture;
class Floor;
class Wall;
class Sofa;
class Table;
class Rack;
class TV;
class Chair;
class Tapete;
class Prato; 
class Sala : public Object {
private:
    std::vector<std::unique_ptr<Object>> components;
    void createRoom();
    void createLivingArea();
    void createDiningArea();
public:
    Sala(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Sala(glm::vec3 pos, float ang);
    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};
#endif
