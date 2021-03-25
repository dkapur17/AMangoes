#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "vertex.hpp"

class TileRenderer
{
public:
    std::vector<Vertex> vertices;
    TileRenderer(Shader &&shader, std::vector<Vertex> vertices);
    ~TileRenderer();
    void DrawTile(glm::vec3 playerPos, glm::vec3 tilePos, bool lights);

private:
    Shader shader;
    unsigned int VAO;
    void initRenderData();
};

#endif