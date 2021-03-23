#include "player.hpp"
#include <iostream>

Player::Player(float stepSizeVal)
    : i(0), j(0), stepSize(stepSizeVal), position(glm::vec3(stepSizeVal / 2, stepSizeVal / 2, 0)), xStep(0.0f), yStep(0.0f) {}

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