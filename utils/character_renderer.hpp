#ifndef CHARACTER_RENDERER_H
#define CHARACTER_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"

class CharacterRenderer
{
public:
    CharacterRenderer(Shader &&shader);
    ~CharacterRenderer();
    void DrawCharacter(glm::vec3 color);

private:
    Shader shader;
    unsigned int VAO;
    void initRenderData();
};

#endif