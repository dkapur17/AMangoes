#include "game.hpp"
#include "resource_manager.hpp"
#include "maze_renderer.hpp"

MazeRenderer *mazeRenderer;

Game::Game(unsigned int width, unsigned int height, unsigned int rows, unsigned int cols)
    : State(GAME_ACTIVE), Keys(std::vector<bool>(1024)), Width(width), Height(height), maze(Maze(rows, cols, width, height)) {}

Game::~Game() {}

void Game::Init()
{
    ResourceManager::LoadShader("shaders/maze.vert", "shaders/maze.frag", "maze");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
                                      static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("maze").Use().SetMatrix4("projection", projection);
    maze.Generate();
    mazeRenderer = new MazeRenderer(ResourceManager::GetShader("maze"), maze.getVertices());
}

void Game::ProcessInput(float dt)
{
}

void Game::Update(float dt)
{
}

void Game::Render()
{
    mazeRenderer->DrawMaze(glm::vec3(1.0f, 1.0f, 1.0f));
}