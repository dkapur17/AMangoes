#ifndef COLLECTABLES_H
#define COLLECTABLES_H

#include <glm/glm.hpp>
#include <vector>
#include "vertex.hpp"

class Gem
{
public:
    int i;
    int j;
    bool collected;
    int cellDim;
    glm::vec3 position;
    int R;
    int G;
    int B;

    Gem(int iVal, int jVal, int cellDimVal);
    std::vector<Vertex> getVertices();
};

class Bomb
{
public:
    int i;
    int j;
    bool collected;
    int cellDim;
    glm::vec3 position;
    int R1;
    int G1;
    int B1;
    int R2;
    int G2;
    int B2;
    int R3;
    int G3;
    int B3;

    Bomb(int iVal, int jVal, int cellDim);
    std::vector<Vertex> getVertices();
};

class CollectablesContainer
{
public:
    bool collectablesReleased;
    int rows;
    int cols;
    int cellDim;
    int gemCount;
    int bombCount;
    std::vector<Gem> gems;
    std::vector<Bomb> bombs;

    CollectablesContainer(int rowsVal, int colsVal, int cellDimVal, int gemCountVal, int bombCountVal);
};

#endif