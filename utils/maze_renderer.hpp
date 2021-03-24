#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "maze.hpp"
#include "vertex.hpp"

class MazeRenderer
{
public:
    std::vector<Vertex> vertices;
    MazeRenderer(Shader &&shader, std::vector<Vertex> vertices);
    ~MazeRenderer();
    void DrawMaze(glm::vec3 color, glm::vec3 playerPos, bool lights);

private:
    Shader shader;
    unsigned int VAO;
    void initRenderData();
};

#endif