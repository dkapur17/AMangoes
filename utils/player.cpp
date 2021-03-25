#include "player.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

Player::Player(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass, int maxLives)
    : i(0), j(0), stepSize(stepSizeVal), position(glm::vec3(stepSizeVal / 2, stepSizeVal / 2, 0)), xStep(0.0f), yStep(0.0f),
      Rb(rBody), Gb(gBody), Bb(bBody), Rg(rGlass), Gg(gGlass), Bg(bGlass), topDist(0), leftDist(0), rightDist(0), bottomDist(0),
      lives(maxLives), score(0), tasksCompleted(0) {}

void Player::Move(char dir, float dt)
{
    if (dir == 'R')
    {
        if (xStep < 0)
            xStep = 0;
        xStep += 10 * dt;
    }
    else if (dir == 'L')
    {
        if (xStep > 0)
            xStep = 0;
        xStep -= 10 * dt;
    }
    else if (dir == 'U')
    {
        if (yStep > 0)
            yStep = 0;
        yStep -= 10 * dt;
    }
    else
    {
        if (yStep < 0)
            yStep = 0;
        yStep += 10 * dt;
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

std::vector<Vertex> Player::getVertices()
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

void Player::computeClosestWalls(Maze maze)
{
    int wi, wj;
    // Left wall
    wj = 0;
    for (int x = 0; x <= j; x++)
        if (maze.grid[i][x].walls["left"])
            wj = x;
    leftDist = (j - wj + 0.5) * maze.grid[i][wj].width;

    // Right wall
    wj = maze.cols - 1;
    for (int x = j; x < maze.cols; x++)
        if (maze.grid[i][x].walls["right"])
        {
            wj = x;
            break;
        }
    rightDist = (wj - j + 0.5) * maze.grid[i][wj].width;

    // Top wall
    wi = 0;
    for (int y = 0; y <= i; y++)
        if (maze.grid[y][j].walls["top"])
            wi = y;
    topDist = (i - wi + 0.5) * maze.grid[wi][j].width;

    // Bottom wall
    wi = maze.rows - 1;
    for (int y = i; y < maze.rows; y++)
        if (maze.grid[y][j].walls["bottom"])
        {
            wi = y;
            break;
        }
    bottomDist = (wi - i + 0.5) * maze.grid[wi][j].width;
}