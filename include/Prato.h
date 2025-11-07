#ifndef PRATO_H
#define PRATO_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Texture; 
class Prato : public Object {
public:
    Prato(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, Texture* plastic = nullptr);
    Prato(glm::vec3 pos, float ang, Texture* plastic = nullptr);
    void init();
    void draw(Shader &shader, glm::mat4 model) override;
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* plasticTexture; 
};
#endif 
