#include "maze_renderer.hpp"

MazeRenderer::MazeRenderer(Shader &&shader, std::vector<MazeVertex> vertices)
{
    this->shader = shader;
    this->vertices = vertices;
    this->initRenderData();
}

MazeRenderer::~MazeRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void MazeRenderer::initRenderData()
{
    unsigned int VBO;
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &(vertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_INT, GL_FALSE, 2 * sizeof(int), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MazeRenderer::DrawMaze(glm::vec3 color)
{
    glm::mat4 model = glm::mat4(1.0f);

    this->shader.Use();
    this->shader.SetVector3f("mazeColor", color);
    this->shader.SetMatrix4("model", model);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);
}