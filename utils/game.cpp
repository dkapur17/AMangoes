#include "game.hpp"
#include "resource_manager.hpp"
#include "tile_renderer.hpp"
#include "task.hpp"
#include <iostream>

Task vaporizeImposter(50, 255, 69, 0);

Game::Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols, unsigned int cellDim)
    : State(GAME_ACTIVE), Keys(std::vector<bool>(1024)), Width(width), Height(height), lights(true),
      maze(Maze(rows, cols, width, height, cellDim)), player(Player((float)cellDim, 128, 205, 50, 240, 248, 255)),
      imposter(Imposter((float)cellDim, 255, 0, 0, 240, 248, 255, rows, cols)),
      initiatedLightClick(false), vaporizeTileRenderer(nullptr),
      mazeRenderer(nullptr), characterRenderer(nullptr) {}

Game::~Game()
{
    delete mazeRenderer;
    delete characterRenderer;
    delete vaporizeTileRenderer;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/env.vert", "shaders/env.frag", "env");
    ResourceManager::LoadShader("shaders/character.vert", "shaders/character.frag", "character");
    glm::mat4 projection = glm::ortho(-static_cast<float>(this->Width) / 2, static_cast<float>(this->Width) / 2,
                                      static_cast<float>(this->Height) / 2, -static_cast<float>(this->Height) / 2, -1.0f, 1.0f);
    ResourceManager::GetShader("env").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("character").Use().SetMatrix4("projection", projection);
    maze.Generate();
    mazeRenderer = new MazeRenderer(ResourceManager::GetShader("env"), maze.getVertices());
    characterRenderer = new CharacterRenderer(ResourceManager::GetShader("character"), ResourceManager::GetShader("env"), player.getVertices(), imposter.getVertices());
    vaporizeTileRenderer = new TileRenderer(ResourceManager::GetShader("env"), vaporizeImposter.getVertices());
}

void Game::ProcessInput(float dt)
{
    if (Keys[GLFW_KEY_RIGHT])
    {
        if (!maze.grid[player.i][player.j].walls["right"])
            player.Move('R', dt);
    }
    else if (Keys[GLFW_KEY_LEFT])
    {
        if (!maze.grid[player.i][player.j].walls["left"])
            player.Move('L', dt);
    }
    else if (Keys[GLFW_KEY_UP])
    {
        if (!maze.grid[player.i][player.j].walls["top"])
            player.Move('U', dt);
    }
    else if (Keys[GLFW_KEY_DOWN])
    {
        if (!maze.grid[player.i][player.j].walls["bottom"])
            player.Move('D', dt);
    }
    else if (Keys[GLFW_KEY_L])
    {
        initiatedLightClick = true;
    }
    if (!Keys[GLFW_KEY_L] && initiatedLightClick)
    {
        initiatedLightClick = false;
        toggleLights();
    }
}

void Game::Update(float dt)
{
    if (player.lives < 1)
    {
        std::cout << "Game Lost\n";
        State = GAME_LOST;
    }
    if (player.i == maze.rows - 1 && player.j == maze.cols - 1 && player.tasksCompleted == 2)
    {
        std::cout << "Game Won\n";
        State = GAME_WON;
    }
    player.computeClosestWalls(maze);
    imposter.computeStep(maze, player, dt);
    if (imposter.i == player.i && imposter.j == player.j)
    {
        std::cout << "Game Lost\n";
        State = GAME_LOST;
    }
}

void Game::Render()
{
    mazeRenderer->DrawMaze(glm::vec3(1.0f, 1.0f, 1.0f), player.position, lights, player.topDist, player.leftDist, player.rightDist, player.bottomDist);
    vaporizeTileRenderer->DrawTile(player.position, vaporizeImposter.position, lights);
    characterRenderer->DrawPlayer();
    characterRenderer->DrawImposter(player.position, imposter.position, lights);
}

void Game::toggleLights()
{
    lights = !lights;
}