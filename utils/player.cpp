#include "player.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>

Player::Player(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass)
    : i(0), j(0), stepSize(stepSizeVal), position(glm::vec3(stepSizeVal / 2, stepSizeVal / 2, 0)), xStep(0.0f), yStep(0.0f),
      Rb(rBody), Gb(gBody), Bb(bBody), Rg(rGlass), Gg(gGlass), Bg(bGlass) {}

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
            Vertex{0.6, 0.5, Rb, Gb, Bb},
            Vertex{0.6, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 0.25, Rb, Gb, Bb},
            // Left Leg
            Vertex{-0.6, 0.5, Rb, Gb, Bb},
            Vertex{-0.6, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 0.25, Rb, Gb, Bb},
        };
    // Head
    for (float x = -0.6; x <= 0.61; x += 0.012)
    {
        float y = -(sqrt((0.5 * 0.5) * (std::max((0.60 * 0.60) - (x * x), 0.0)) / (0.60 * 0.60)) + 0.5);
        vertices.push_back(Vertex{x, y, Rb, Gb, Bb});
    }
    // Glasses
    vertices.push_back({-0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back({0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back({0.4, 0, Rg, Gg, Bg});
    vertices.push_back({-0.4, 0, Rg, Gg, Bg});

    return vertices;
}