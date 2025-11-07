#ifndef VASOSANITARIO_H
#define VASOSANITARIO_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Texture; 
class VasoSanitario : public Object {
public:
    VasoSanitario(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
                  Texture* plastic = nullptr);
    VasoSanitario(glm::vec3 pos, float ang, 
                  Texture* plastic = nullptr);
    void init();
    void draw(Shader &shader, glm::mat4 model) override;
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* plasticTexture; 
};
#endif 
