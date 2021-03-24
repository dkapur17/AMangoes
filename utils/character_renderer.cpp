#include <iostream>
#include <vector>

#include "character_renderer.hpp"
#include "vertex.hpp"

CharacterRenderer::CharacterRenderer(Shader &&shader, std::vector<Vertex> playerVertices, std::vector<Vertex> imposterVertices)
{
    this->shader = shader;
    this->initRenderData(playerVertices, imposterVertices);
}

CharacterRenderer::~CharacterRenderer()
{
    glDeleteVertexArrays(1, &this->PlayerVAO);
}

void CharacterRenderer::initRenderData(std::vector<Vertex> playerVertices, std::vector<Vertex> imposterVertices)
{
    unsigned int PlayerVBO;
    glGenVertexArrays(1, &this->PlayerVAO);
    glGenBuffers(1, &PlayerVBO);

    glBindVertexArray(this->PlayerVAO);

    glBindBuffer(GL_ARRAY_BUFFER, PlayerVBO);
    glBufferData(GL_ARRAY_BUFFER, playerVertices.size() * sizeof(Vertex), &(playerVertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, R));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int ImposterVBO;
    glGenVertexArrays(1, &this->ImposterVAO);
    glGenBuffers(1, &ImposterVBO);

    glBindVertexArray(this->ImposterVAO);

    glBindBuffer(GL_ARRAY_BUFFER, ImposterVBO);
    glBufferData(GL_ARRAY_BUFFER, imposterVertices.size() * sizeof(Vertex), &(imposterVertices[0]), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, R));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CharacterRenderer::DrawPlayer()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));

    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    glBindVertexArray(this->PlayerVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 101);
    glDrawArrays(GL_TRIANGLE_FAN, 113, 4);
    glBindVertexArray(0);
}

void CharacterRenderer::DrawImposter(glm::vec3 playerPos, glm::vec3 imposterPos)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, -playerPos);
    model = glm::translate(model, imposterPos);
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));
    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    glBindVertexArray(this->ImposterVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 101);
    glDrawArrays(GL_TRIANGLE_FAN, 113, 4);
    glBindVertexArray(0);
}