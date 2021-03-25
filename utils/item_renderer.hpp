#ifndef ITEM_RENDERER_H
#define ITEM_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "vertex.hpp"

class ItemRenderer
{
public:
    std::vector<Vertex> gemVertices;
    std::vector<Vertex> bombVertices;
    ItemRenderer(Shader &&shader, std::vector<Vertex> gemVertices, std::vector<Vertex> bombVertices);
    ~ItemRenderer();
    void DrawGem(glm::vec3 playerPos, glm::vec3 gemPos, bool lights);
    void DrawBomb(glm::vec3 playerPos, glm::vec3 bombPos, bool lights);

private:
    Shader shader;
    unsigned int gemVAO;
    unsigned int bombVAO;
    void initRenderData();
};

#endif