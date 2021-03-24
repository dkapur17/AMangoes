#include "game.hpp"
#include "resource_manager.hpp"

Game::Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols, unsigned int cellDim)
    : State(GAME_ACTIVE), Keys(std::vector<bool>(1024)), Width(width), Height(height), lights(true),
      maze(Maze(rows, cols, width, height, cellDim)), player(Player((float)cellDim, 128, 205, 50, 240, 248, 255)),
      imposter(Imposter((float)cellDim, 255, 0, 0, 240, 248, 255, rows, cols)),
      initiatedLightClick(false),
      mazeRenderer(nullptr), characterRenderer(nullptr) {}

Game::~Game() {}

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
    player.computeClosestWalls(maze);
    imposter.computeStep(maze, player, dt);
}

void Game::Render()
{
    mazeRenderer->DrawMaze(glm::vec3(1.0f, 1.0f, 1.0f), player.position, lights, player.topDist, player.leftDist, player.rightDist, player.bottomDist);
    characterRenderer->DrawPlayer();
    characterRenderer->DrawImposter(player.position, imposter.position, lights);
}

void Game::toggleLights()
{
    lights = !lights;
}