#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <map>

#include "vertex.hpp"

class Cell
{
public:
    int i;
    int j;
    int height;
    int width;
    std::map<std::string, bool> walls;
    bool visited;

    Cell(int iVal, int jVal, int wVal, int hVal);
};

class Maze
{
public:
    std::vector<std::vector<Cell>> grid;
    unsigned int rows;
    unsigned int cols;

    Maze(unsigned int rowsVal, unsigned int colsVal, unsigned int screenWidth, unsigned int screenHeight, int cellDim);
    void Generate();
    std::vector<Vertex> getVertices();

private:
    Cell *checkNeighbours(Cell *current);
    void removeWalls(Cell *current, Cell *next);
};

#endif