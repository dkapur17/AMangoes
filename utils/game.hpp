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
#include "imposter.hpp"

enum GameState
{
    GAME_ACTIVE,
    GAME_WON,
    GAME_LOST
};

class Game
{
public:
    GameState State;
    std::vector<bool> Keys;
    unsigned int width, height, rows, cols, cellDim;
    Maze maze;
    Player player;
    Imposter imposter;

    Game(unsigned int widthVal, unsigned int heightVal, unsigned int rowsVal, unsigned int colsVal, unsigned int cellDimVal);
    ~Game();

    void Init();
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    void toggleLights();

private:
    bool lights;
    bool initiatedLightClick;
};

#endif