#ifndef TAPETE_H
#define TAPETE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Texture; 
class Tapete : public Object {
public:
    Tapete(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* fabric = nullptr);
    Tapete(glm::vec3 pos, float ang, Texture* fabric = nullptr);
    void init();
    void draw(Shader &shader, glm::mat4 model) override;
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* fabricTexture; 
};
#endif 
