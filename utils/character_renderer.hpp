#ifndef CHARACTER_RENDERER_H
#define CHARACTER_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "vertex.hpp"

class CharacterRenderer
{
public:
    CharacterRenderer(Shader &&shader, std::vector<Vertex> vertices);
    ~CharacterRenderer();
    void DrawCharacter();

private:
    Shader shader;
    unsigned int VAO;
    void initRenderData(std::vector<Vertex> vertices);
};

#endif