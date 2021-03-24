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
    CharacterRenderer(Shader &&playerShader, Shader &&imposterShader, std::vector<Vertex> playerVertices, std::vector<Vertex> imposterVertices);
    ~CharacterRenderer();
    void DrawPlayer();
    void DrawImposter(glm::vec3 playerPos, glm::vec3 imposterPos, bool lightsOn);

private:
    Shader playerShader;
    Shader imposterShader;
    unsigned int PlayerVAO;
    unsigned int ImposterVAO;
    void initRenderData(std::vector<Vertex> vertices, std::vector<Vertex> imposterVertices);
};

#endif