#ifndef PORTA_H
#define PORTA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Porta : public Object {
private:
    std::vector<std::unique_ptr<Object>> parts;
public:
    Porta(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang);
    Porta(glm::vec3 pos, float ang);
    void init();
    void draw(Shader& shader, glm::mat4 model) override;
};
#endif
