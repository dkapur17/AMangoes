#ifndef IMPOSTER_H
#define IMPOSTER_H

#include <glm/glm.hpp>
#include <vector>
#include "vertex.hpp"
#include "maze.hpp"
#include "player.hpp"

class Imposter
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
    bool active;

    Imposter(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass, int rows, int cols);
    void Move(char dir, float dt);
    std::vector<Vertex> getVertices();
    void computeStep(Maze maze, Player player, float dt);
};

#endif