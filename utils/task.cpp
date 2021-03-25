#include "task.hpp"
#include "random_engine.hpp"
#include <iostream>

Task::Task(int cellDimVal, int RVal, int GVal, int BVal, int rows, int cols, bool isFinish)
    : cellDim(cellDimVal), R(RVal), G(GVal), B(BVal), completed(false),
      i(RandomEngine::randomInt(0, rows - 1)), j(RandomEngine::randomInt(0, cols - 1)),
      position(glm::vec3((2 * j + 1) * cellDim / 2, (2 * i + 1) * cellDim / 2, 0.0f)), isFinishTile(isFinish) {}

std::vector<Vertex> Task::getVertices()
{
    float tileDim = (cellDim / 2) - 1;
    std::vector<Vertex> vertices;
    if (!isFinishTile)
        vertices = {
            Vertex{tileDim, tileDim, R, G, B},
            Vertex{-tileDim, tileDim, R, G, B},
            Vertex{-tileDim, -tileDim, R, G, B},
            Vertex{tileDim, -tileDim, R, G, B}};
    else
        vertices = {
            Vertex{tileDim, 0, R, G, B},
            Vertex{0, tileDim, R, G, B},
            Vertex{-tileDim, 0, R, G, B},
            Vertex{0, -tileDim, R, G, B}};
    return vertices;
}