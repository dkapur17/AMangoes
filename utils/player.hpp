#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

class Player
{
public:
    int i;
    int j;
    float xStep;
    float yStep;
    float stepSize;
    glm::vec3 position;

    Player(float stepSizeVal);
    void Move(char dir, float dt);
};

#endif