#ifndef BANHEIRO_H
#define BANHEIRO_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Floor;
class Wall;
class Pia;
class VasoSanitario;
class Banheiro : public Object {
private:
    std::vector<std::unique_ptr<Object>> components;
    void createRoom();
    void createFixtures();
public:
    Banheiro(glm::vec3 pos, float ang);
    void init();
    void draw(Shader& shader, glm::mat4 parentTransform) override;
};
#endif 
