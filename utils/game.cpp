#include "game.hpp"
#include "resource_manager.hpp"
#include "maze_renderer.hpp"
#include "character_renderer.hpp"

MazeRenderer *mazeRenderer;
CharacterRenderer *characterRenderer;

Game::Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols, unsigned int cellDim)
    : State(GAME_ACTIVE), Keys(std::vector<bool>(1024)), Width(width), Height(height), lights(true),
      maze(Maze(rows, cols, width, height, cellDim)), player(Player((float)cellDim)), initiatedLightClick(false) {}

Game::~Game() {}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/maze.vert", "shaders/maze.frag", "maze");
    ResourceManager::LoadShader("shaders/character.vert", "shaders/character.frag", "character");
    glm::mat4 projection = glm::ortho(-static_cast<float>(this->Width) / 2, static_cast<float>(this->Width) / 2,
                                      static_cast<float>(this->Height) / 2, -static_cast<float>(this->Height) / 2, -1.0f, 1.0f);
    ResourceManager::GetShader("maze").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("character").Use().SetMatrix4("projection", projection);
    maze.Generate();
    mazeRenderer = new MazeRenderer(ResourceManager::GetShader("maze"), maze.getVertices());
    characterRenderer = new CharacterRenderer(ResourceManager::GetShader("character"));
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
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

void Game::Render()
{
    mazeRenderer->DrawMaze(glm::vec3(1.0f, 1.0f, 1.0f), player.position, lights);
    characterRenderer->DrawCharacter(glm::vec3(1.0f, 0.0f, 0.0f));
}

void Game::toggleLights()
{
    lights = !lights;
}