#include "item_renderer.hpp"

ItemRenderer::ItemRenderer(Shader &&shader, std::vector<Vertex> gemVertices, std::vector<Vertex> bombVertices)
{
    this->shader = shader;
    this->gemVertices = gemVertices;
    this->bombVertices = bombVertices;
    this->initRenderData();
}

ItemRenderer::~ItemRenderer() {}

void ItemRenderer::initRenderData()
{
    unsigned int gemVBO;
    glGenVertexArrays(1, &this->gemVAO);
    glGenBuffers(1, &gemVBO);

    glBindVertexArray(this->gemVAO);

    glBindBuffer(GL_ARRAY_BUFFER, gemVBO);
    glBufferData(GL_ARRAY_BUFFER, gemVertices.size() * sizeof(Vertex), &(gemVertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, R));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int bombVBO;
    glGenVertexArrays(1, &this->bombVAO);
    glGenBuffers(1, &bombVBO);

    glBindVertexArray(this->bombVAO);

    glBindBuffer(GL_ARRAY_BUFFER, bombVBO);
    glBufferData(GL_ARRAY_BUFFER, bombVertices.size() * sizeof(Vertex), &(bombVertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, R));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ItemRenderer::DrawGem(glm::vec3 playerPos, glm::vec3 gemPos, bool lightsOn)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -playerPos);
    model = glm::translate(model, gemPos);

    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    this->shader.SetInteger("lights", lightsOn);
    glBindVertexArray(this->gemVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, gemVertices.size());
    glBindVertexArray(0);
}

void ItemRenderer::DrawBomb(glm::vec3 playerPos, glm::vec3 bombPos, bool lightsOn)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -playerPos);
    model = glm::translate(model, bombPos);

    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    this->shader.SetInteger("lights", lightsOn);
    glBindVertexArray(this->bombVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glBindVertexArray(0);
}