#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "vertex.hpp"

class Player
{
public:
    int i;
    int j;
    float xStep;
    float yStep;
    float stepSize;
    glm::vec3 position;
    int Rb;
    int Gb;
    int Bb;
    int Rg;
    int Gg;
    int Bg;

    Player(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass);
    void Move(char dir, float dt);
    std::vector<Vertex> getVertices();
};

#endif