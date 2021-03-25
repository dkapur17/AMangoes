#include "tile_renderer.hpp"

TileRenderer::TileRenderer(Shader &&shader, std::vector<Vertex> vertices)
{
    this->shader = shader;
    this->vertices = vertices;
    this->initRenderData();
}

TileRenderer::~TileRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void TileRenderer::initRenderData()
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

void TileRenderer::DrawTile(glm::vec3 playerPos, glm::vec3 tilePos, bool lightsOn)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -playerPos);
    model = glm::translate(model, tilePos);

    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    this->shader.SetInteger("lights", lightsOn);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
    glBindVertexArray(0);
}