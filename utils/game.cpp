#include "game.hpp"
#include "resource_manager.hpp"
#include "tile_renderer.hpp"
#include "maze_renderer.hpp"
#include "character_renderer.hpp"
#include "task.hpp"
#include "collectables.hpp"
#include "item_renderer.hpp"
#include <iostream>

MazeRenderer *mazeRenderer = nullptr;
CharacterRenderer *characterRenderer = nullptr;
TileRenderer *vaporizeTileRenderer = nullptr;
TileRenderer *releaseTileRenderer = nullptr;
TileRenderer *finishTileRenderer = nullptr;
ItemRenderer *itemRenderer = nullptr;

Task *vaporizeImposter = nullptr;
Task *releaseItems = nullptr;
Task *finishLine = nullptr;

CollectablesContainer *container = nullptr;
Game::Game(unsigned int widthVal, unsigned int heightVal, unsigned int rowsVal, unsigned int colsVal, unsigned int cellDimVal, unsigned int timeLimitVal)
    : State(GAME_ACTIVE), Keys(std::vector<bool>(1024)), width(widthVal), height(heightVal), rows(rowsVal), cols(colsVal), cellDim(cellDimVal), lights(true),
      maze(Maze(rows, cols, width, height, cellDim)), player(Player((float)cellDim, 128, 205, 50, 240, 248, 255, 5)),
      imposter(Imposter((float)cellDim, 255, 0, 0, 240, 248, 255, rows, cols)), gameDuration(timeLimitVal), timeLeft(timeLimitVal),
      initiatedLightClick(false), scoreUpdated(false)
{
    vaporizeImposter = new Task(cellDim, 255, 69, 0, rows, cols, false);
    releaseItems = new Task(cellDim, 0, 117, 117, rows, cols, false);
    finishLine = new Task(cellDim, 0, 191, 255, rows, cols, true);

    container = new CollectablesContainer(rows, cols, cellDim, 10, 10);
}

Game::~Game()
{
    // Renderers
    delete mazeRenderer;
    delete characterRenderer;
    delete vaporizeTileRenderer;
    delete releaseTileRenderer;
    delete itemRenderer;

    // Tasks
    delete vaporizeImposter;
    delete releaseItems;

    // Collectables
    delete container;
}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/env.vert", "shaders/env.frag", "env");
    ResourceManager::LoadShader("shaders/character.vert", "shaders/character.frag", "character");
    glm::mat4 projection = glm::ortho(-static_cast<float>(this->width) / 2, static_cast<float>(this->width) / 2,
                                      static_cast<float>(this->height) / 2, -static_cast<float>(this->height) / 2, -1.0f, 1.0f);
    ResourceManager::GetShader("env").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("character").Use().SetMatrix4("projection", projection);
    maze.Generate();
    mazeRenderer = new MazeRenderer(ResourceManager::GetShader("env"), maze.getVertices());
    characterRenderer = new CharacterRenderer(ResourceManager::GetShader("character"), ResourceManager::GetShader("env"), player.getVertices(), imposter.getVertices());
    vaporizeTileRenderer = new TileRenderer(ResourceManager::GetShader("env"), vaporizeImposter->getVertices());
    releaseTileRenderer = new TileRenderer(ResourceManager::GetShader("env"), releaseItems->getVertices());
    finishTileRenderer = new TileRenderer(ResourceManager::GetShader("env"), finishLine->getVertices());
    itemRenderer = new ItemRenderer(ResourceManager::GetShader("env"), container->gems[0].getVertices(), container->bombs[0].getVertices());
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

void Game::Update(float dt, int clockTime)
{
    timeLeft = gameDuration - clockTime;
    if (timeLeft <= 0)
        State = GAME_LOST;
    if (clockTime > 0 && clockTime % 2 == 0 && !scoreUpdated)
    {
        player.score += (lights ? 1 : 5);
        scoreUpdated = true;
    }
    else if (clockTime % 2 != 0)
        scoreUpdated = false;
    if (container->collectablesReleased)
    {
        for (Gem &gem : container->gems)
            if (!gem.collected && player.i == gem.i && player.j == gem.j)
            {
                gem.collected = true;
                player.score += 25;
            }

        for (Bomb &bomb : container->bombs)
            if (!bomb.collected && player.i == bomb.i && player.j == bomb.j)
            {
                bomb.collected = true;
                player.lives--;
            }
    }
    if (player.lives < 1)
        State = GAME_LOST;
    if (player.i == finishLine->i && player.j == finishLine->j && player.tasksCompleted == 2)
        State = GAME_WON;
    if (player.i == vaporizeImposter->i && player.j == vaporizeImposter->j && imposter.active)
    {
        imposter.active = false;
        player.tasksCompleted += 1;
    }
    if (player.i == releaseItems->i && player.j == releaseItems->j && !container->collectablesReleased)
    {
        container->collectablesReleased = true;
        player.tasksCompleted += 1;
    }
    player.computeClosestWalls(maze);
    if (imposter.active)
    {
        imposter.computeStep(maze, player, dt);
        if (imposter.i == player.i && imposter.j == player.j)
            State = GAME_LOST;
    }
}

void Game::Render()
{
    mazeRenderer->DrawMaze(glm::vec3(1.0f, 1.0f, 1.0f), player.position, lights, player.topDist, player.leftDist, player.rightDist, player.bottomDist);
    if (imposter.active)
        vaporizeTileRenderer->DrawTile(player.position, vaporizeImposter->position, lights);
    if (!container->collectablesReleased)
        releaseTileRenderer->DrawTile(player.position, releaseItems->position, lights);
    if (player.tasksCompleted == 2)
        finishTileRenderer->DrawTile(player.position, finishLine->position, lights);
    if (container->collectablesReleased)
    {
        for (Gem gem : container->gems)
            if (!gem.collected)
                itemRenderer->DrawGem(player.position, gem.position, lights);
        for (Bomb bomb : container->bombs)
            if (!bomb.collected)
                itemRenderer->DrawBomb(player.position, bomb.position, lights);
    }
    characterRenderer->DrawPlayer();
    if (imposter.active)
        characterRenderer->DrawImposter(player.position, imposter.position, lights);
}

void Game::toggleLights()
{
    lights = !lights;
}