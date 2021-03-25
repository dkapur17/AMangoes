#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <vector>
#include "vertex.hpp"
#include "maze.hpp"

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
    int lives;
    int score;
    int tasksCompleted;

    float topDist;
    float leftDist;
    float rightDist;
    float bottomDist;

    Player(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass, int maxLives);
    void Move(char dir, float dt);
    std::vector<Vertex> getVertices();
    void computeClosestWalls(Maze maze);
};

#endif