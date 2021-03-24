#include "maze_renderer.hpp"

MazeRenderer::MazeRenderer(Shader &&shader, std::vector<Vertex> vertices)
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
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, R));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MazeRenderer::DrawMaze(glm::vec3 color, glm::vec3 playerPos, bool lightsOn, float topDist, float leftDist, float rightDist, float bottomDist)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -playerPos);

    this->shader.Use();
    this->shader.SetVector3f("mazeColor", color);
    this->shader.SetMatrix4("model", model);
    this->shader.SetInteger("lights", lightsOn);
    this->shader.SetFloat("topDist", topDist);
    this->shader.SetFloat("leftDist", leftDist);
    this->shader.SetFloat("rightDist", rightDist);
    this->shader.SetFloat("bottomDist", bottomDist);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, vertices.size());
    glBindVertexArray(0);
}