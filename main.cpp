#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ctime>
#include <cstdio>

#define GLT_IMPLEMENTATION
#include "lib/glText.h"

#include "utils/game.hpp"
#include "utils/resource_manager.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

Game AMangoes(SCREEN_WIDTH, SCREEN_HEIGHT, 25, 25, 50, 180);

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AMangoes", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gltInit())
    {
        std::cout << "Failed to initialize glText" << std::endl;
        glfwTerminate();
        return -1;
    }
    GLTtext *onScreenText = gltCreateText();
    char textContent[500];

    GLTtext *victoryText = gltCreateText();
    gltSetText(victoryText, "Victory");

    GLTtext *defeatText = gltCreateText();
    gltSetText(defeatText, "Defeat");

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    AMangoes.Init();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        int clockTime = clock() / CLOCKS_PER_SEC;
        glfwPollEvents();

        if (AMangoes.State == GAME_ACTIVE)
        {
            AMangoes.ProcessInput(deltaTime);
            AMangoes.Update(deltaTime, clockTime);
        }
        sprintf(textContent, "Time Left: %d\nLives: %d\nScore: %d\nLights: %s\nTasks Completed: %d/2", AMangoes.timeLeft, AMangoes.player.lives, AMangoes.player.score, (AMangoes.lights ? "On" : "Off"), AMangoes.player.tasksCompleted);
        gltSetText(onScreenText, textContent);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (AMangoes.State == GAME_ACTIVE)
            AMangoes.Render();

        gltBeginDraw();
        if (AMangoes.State == GAME_ACTIVE)
        {
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2D(onScreenText, 0.0f, 0.0f, 1.0f);
        }
        else if (AMangoes.State == GAME_WON)
        {
            sprintf(textContent, "Final Score: %d", AMangoes.player.score);
            gltColor(0.0f, 1.0f, 0.0f, 1.0f);
            gltDrawText2DAligned(victoryText,
                                 (GLfloat)(SCREEN_WIDTH / 2),
                                 (GLfloat)(SCREEN_HEIGHT / 4),
                                 7.0f,
                                 GLT_CENTER, GLT_CENTER);
            gltSetText(onScreenText, textContent);
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2DAligned(onScreenText,
                                 (GLfloat)(SCREEN_WIDTH / 2),
                                 (GLfloat)(SCREEN_HEIGHT / 2),
                                 2.0f,
                                 GLT_CENTER, GLT_CENTER);
        }
        else
        {
            sprintf(textContent, "Final Score: %d", AMangoes.player.score);
            gltColor(1.0f, 0.0f, 0.0f, 1.0f);
            gltDrawText2DAligned(defeatText,
                                 (GLfloat)(SCREEN_WIDTH / 2),
                                 (GLfloat)(SCREEN_HEIGHT / 4),
                                 7.0f,
                                 GLT_CENTER, GLT_CENTER);
            gltSetText(onScreenText, textContent);
            gltColor(1.0f, 1.0f, 1.0f, 1.0f);
            gltDrawText2DAligned(onScreenText,
                                 (GLfloat)(SCREEN_WIDTH / 2),
                                 (GLfloat)(SCREEN_HEIGHT / 2),
                                 2.0f,
                                 GLT_CENTER, GLT_CENTER);
        }
        gltEndDraw();

        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            AMangoes.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            AMangoes.Keys[key] = false;
    }
}