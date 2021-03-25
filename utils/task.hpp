#ifndef TASK_H
#define TASK_H

#include <glm/glm.hpp>
#include <vector>
#include "vertex.hpp"

class Task
{
public:
    int i;
    int j;
    int cellDim;
    glm::vec3 position;
    int R;
    int G;
    int B;
    bool completed;
    bool isFinishTile;

    Task(int cellDimVal, int RVal, int GVal, int BVal, int rows, int cols, bool isFinish);
    std::vector<Vertex> getVertices();
};

#endif