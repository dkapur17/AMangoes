#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "shader.hpp"
#include "maze.hpp"

class MazeRenderer
{
public:
    std::vector<MazeVertex> vertices;
    MazeRenderer(Shader &&shader, std::vector<MazeVertex> vertices);
    ~MazeRenderer();
    void DrawMaze(glm::vec3 color, glm::vec3 playerPos, bool lights);

private:
    Shader shader;
    unsigned int VAO;
    void initRenderData();
};

#endif