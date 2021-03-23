#include "character_renderer.hpp"
#include <iostream>

CharacterRenderer::CharacterRenderer(Shader &&shader)
{
    this->shader = shader;
    this->initRenderData();
}

CharacterRenderer::~CharacterRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void CharacterRenderer::initRenderData()
{
    float vertices[] = {
        0.5, 1.0,
        0.5, -1.0,
        -0.5, -1.0,
        -0.5, 1.0};
    unsigned int VBO;
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CharacterRenderer::DrawCharacter(glm::vec3 color)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(20.0f, 20.0f, 1.0f));

    this->shader.Use();
    this->shader.SetVector3f("characterColor", color);
    this->shader.SetMatrix4("model", model);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glBindVertexArray(0);
}