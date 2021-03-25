#include "imposter.hpp"
#include <iostream>
#include <stack>
#include <queue>
#include <map>
#include <utility>
#include "random_engine.hpp"

Imposter::Imposter(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass, int rows, int cols)
    : stepSize(stepSizeVal), Rb(rBody), Gb(gBody), Bb(bBody), Rg(rGlass), Gg(gGlass), Bg(bGlass), active(true)
{
    i = RandomEngine::randomInt(0, rows - 1);
    j = RandomEngine::randomInt(0, cols - 1);

    position = glm::vec3((2 * j + 1) * stepSize / 2, (2 * i + 1) * stepSize / 2, 0);
}
void Imposter::Move(char dir, float dt)
{
    float imposterSpeed = 3.0;
    if (dir == 'R')
    {
        if (xStep < 0)
            xStep = 0;
        xStep += 1 * imposterSpeed * dt;
    }
    else if (dir == 'L')
    {
        if (xStep > 0)
            xStep = 0;
        xStep -= 1 * imposterSpeed * dt;
    }
    else if (dir == 'U')
    {
        if (yStep > 0)
            yStep = 0;
        yStep -= 1 * imposterSpeed * dt;
    }
    else
    {
        if (yStep < 0)
            yStep = 0;
        yStep += 1 * imposterSpeed * dt;
    }

    if (xStep >= 1)
    {
        j += 1;
        xStep = 0;
    }
    else if (xStep <= -1)
    {
        j -= 1;
        xStep = 0;
    }
    else if (yStep >= 1)
    {
        i += 1;
        yStep = 0;
    }
    else if (yStep <= -1)
    {
        i -= 1;
        yStep = 0;
    }

    position = glm::vec3((2 * j + 1) * stepSize / 2, (2 * i + 1) * stepSize / 2, 0.0f);
}

std::vector<Vertex> Imposter::getVertices()
{
    std::vector<Vertex> vertices =
        {
            // Body
            Vertex{0.6, -0.5, Rb, Gb, Bb},
            Vertex{0.6, 0.7, Rb, Gb, Bb},
            Vertex{-0.6, 0.7, Rb, Gb, Bb},
            Vertex{-0.6, -0.5, Rb, Gb, Bb},
            // Right Leg
            Vertex{0.6, 0.7, Rb, Gb, Bb},
            Vertex{0.6, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 0.7, Rb, Gb, Bb},
            // Left Leg
            Vertex{-0.6, 0.7, Rb, Gb, Bb},
            Vertex{-0.6, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 0.7, Rb, Gb, Bb},
        };
    // Head
    for (float x = -0.6; x <= 0.61; x += 0.012)
    {
        float y = -(sqrt((0.5 * 0.5) * (std::max((0.60 * 0.60) - (x * x), 0.0)) / (0.60 * 0.60)) + 0.5);
        vertices.push_back(Vertex{x, y, Rb, Gb, Bb});
    }
    // Glasses
    vertices.push_back(Vertex{-0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back(Vertex{0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back(Vertex{0.4, 0, Rg, Gg, Bg});
    vertices.push_back(Vertex{-0.4, 0, Rg, Gg, Bg});

    return vertices;
}

void Imposter::computeStep(Maze maze, Player player, float dt)
{
    Cell *current = &maze.grid[i][j];
    std::queue<Cell *> q;
    std::map<std::pair<int, int>, int> dist;
    dist[{current->i, current->j}] = 0;
    current->visited = true;
    q.push(current);
    while (!q.empty())
    {
        current = q.front();
        int parentDistance = dist[{current->i, current->j}];
        q.pop();
        for (Cell *next : maze.getNeighbours(current))
            if (!next->visited)
            {
                q.push(next);
                next->visited = true;
                dist[{next->i, next->j}] = parentDistance + 1;
            }
    }

    int playerDist = dist[{player.i, player.j}];
    std::stack<Cell *> path;
    path.push(&maze.grid[player.i][player.j]);
    while (playerDist > 1)
    {
        current = path.top();
        for (Cell *next : maze.getNeighbours(current))
            if (dist[{next->i, next->j}] == playerDist - 1)
            {
                path.push(next);
                playerDist -= 1;
                break;
            }
    }

    Cell *nextStep = path.top();
    current = &maze.grid[i][j];

    if (nextStep->i == current->i)
    {
        if (nextStep->j < current->j)
            Move('L', dt);
        else if (nextStep->j > current->j)
            Move('R', dt);
    }
    else if (nextStep->j == current->j)
    {
        if (nextStep->i < current->i)
            Move('U', dt);
        else if (nextStep->i > current->i)
            Move('D', dt);
    }
}