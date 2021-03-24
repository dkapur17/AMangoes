#include <iostream>
#include <vector>

#include "character_renderer.hpp"
#include "vertex.hpp"

CharacterRenderer::CharacterRenderer(Shader &&shader, std::vector<Vertex> vertices)
{
    this->shader = shader;
    this->initRenderData(vertices);
}

CharacterRenderer::~CharacterRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void CharacterRenderer::initRenderData(std::vector<Vertex> vertices)
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

void CharacterRenderer::DrawCharacter()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));

    this->shader.Use();
    ;
    this->shader.SetMatrix4("model", model);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 101);
    glDrawArrays(GL_TRIANGLE_FAN, 113, 4);
    glBindVertexArray(0);
}