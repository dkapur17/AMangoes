#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "maze.hpp"
#include "player.hpp"

enum GameState
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState State;
    std::vector<bool> Keys;
    unsigned int Width, Height;
    Maze maze;
    Player player;

    Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols, unsigned int cellDim);
    ~Game();

    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

#endif