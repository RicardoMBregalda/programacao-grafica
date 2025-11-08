#ifndef PIA_H
#define PIA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Object.h"
#include "Shader.h"
#include <vector>
#include <memory>
class Texture; 
class Pia : public Object {
public:
    Pia(glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, float ang, 
        Texture* wood = nullptr, Texture* ceramic = nullptr, Texture* plastic = nullptr);
    Pia(glm::vec3 pos, float ang, 
        Texture* wood = nullptr, Texture* ceramic = nullptr, Texture* plastic = nullptr);
    void init();
    void draw(Shader &shader, glm::mat4 model) override;
private:
    std::vector<std::unique_ptr<Object>> parts;
    Texture* woodTexture;      
    Texture* ceramicTexture;   
    Texture* plasticTexture;   
};
#endif 
