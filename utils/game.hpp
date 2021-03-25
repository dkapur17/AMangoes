#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "maze_renderer.hpp"
#include "character_renderer.hpp"
#include "tile_renderer.hpp"
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
    unsigned int Width, Height;
    MazeRenderer *mazeRenderer;
    CharacterRenderer *characterRenderer;
    TileRenderer *vaporizeTileRenderer;
    Maze maze;
    Player player;
    Imposter imposter;

    Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols, unsigned int cellDim);
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