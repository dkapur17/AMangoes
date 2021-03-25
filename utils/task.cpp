#include "task.hpp"
#include <iostream>

Task::Task(int cellDimVal, int RVal, int GVal, int BVal)
    : cellDim(cellDimVal), R(RVal), G(GVal), B(BVal), completed(false)
{
    i = 5;
    j = 5;
    position = glm::vec3((2 * j + 1) * cellDim / 2, (2 * i + 1) * cellDim / 2, 0.0f);
}

std::vector<Vertex> Task::getVertices()
{
    std::vector<Vertex> vertices = {
        Vertex{24, 24, R, G, B},
        Vertex{-24, 24, R, G, B},
        Vertex{-24, -24, R, G, B},
        Vertex{24, -24, R, G, B}};
    return vertices;
}