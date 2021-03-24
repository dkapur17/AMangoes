#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <algorithm>
#include "maze.hpp"

Cell::Cell(int iVal, int jVal, int wVal, int hVal)
    : i(iVal), j(jVal), width(wVal), height(hVal), visited(false)
{
    walls["top"] = true;
    walls["bottom"] = true;
    walls["left"] = true;
    walls["right"] = true;
}

Maze::Maze(unsigned int rowsVal, unsigned int colsVal, unsigned int screenWidth, unsigned int screenHeight, int cellDim) : rows(rowsVal), cols(colsVal)
{
    for (int i = 0; i < rows; i++)
    {
        std::vector<Cell> row;
        for (int j = 0; j < cols; j++)
            row.push_back(Cell(i, j, cellDim, cellDim));
        grid.push_back(row);
    }
}

void Maze::Generate()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> rowDist(0, rows - 1);
    std::uniform_int_distribution<> colDist(0, cols - 1);
    int startRow = rowDist(rng);
    int startCol = colDist(rng);

    Cell *current = &grid[startRow][startCol];
    current->visited = true;
    std::stack<Cell *> s;
    int visitCount = 1;
    while (visitCount < rows * cols)
    {
        Cell *next = checkNeighbours(current);
        if (next)
        {
            visitCount++;
            s.push(current);
            next->visited = true;
            removeWalls(current, next);
            current = next;
        }
        else if (!s.empty())
        {
            current = s.top();
            s.pop();
        }
    }

    // Introduce Cycles
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            Cell *current = &grid[i][j];
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_real_distribution<> dist(0.0f, 1.0f);
            float breakWallProb = dist(rng);
            if (breakWallProb <= 0.05)
            {
                std::vector<Cell *> walledNeighbours;
                if (i != 0 && current->walls["top"])
                    walledNeighbours.push_back(&grid[i - 1][j]);
                if (i != rows - 1 && current->walls["bottom"])
                    walledNeighbours.push_back(&grid[i + 1][j]);
                if (j != 0 && current->walls["left"])
                    walledNeighbours.push_back(&grid[i][j - 1]);
                if (j != cols - 1 && current->walls["right"])
                    walledNeighbours.push_back(&grid[i][j + 1]);

                if (walledNeighbours.size())
                {
                    std::default_random_engine re(rd());
                    std::shuffle(std::begin(walledNeighbours), std::end(walledNeighbours), re);
                    removeWalls(current, walledNeighbours[0]);
                }
            }
            current->visited = false;
        }
}

void Maze::removeWalls(Cell *current, Cell *next)
{
    int y = current->i - next->i;
    int x = current->j - next->j;
    if (y == 1)
    {
        current->walls["top"] = false;
        next->walls["bottom"] = false;
    }
    else if (y == -1)
    {
        current->walls["bottom"] = false;
        next->walls["top"] = false;
    }
    else if (x == 1)
    {
        current->walls["left"] = false;
        next->walls["right"] = false;
    }
    else if (x == -1)
    {
        current->walls["right"] = false;
        next->walls["left"] = false;
    }
}

Cell *Maze::checkNeighbours(Cell *current)
{
    std::vector<Cell *> neighbours;
    Cell *top = nullptr, *bottom = nullptr, *left = nullptr, *right = nullptr;
    if (current->i > 0)
        top = &grid[current->i - 1][current->j];
    if (current->i < cols - 1)
        bottom = &grid[current->i + 1][current->j];
    if (current->j > 0)
        left = &grid[current->i][current->j - 1];
    if (current->j < rows - 1)
        right = &grid[current->i][current->j + 1];

    if (top && !top->visited)
        neighbours.push_back(top);
    if (bottom && !bottom->visited)
        neighbours.push_back(bottom);
    if (left && !left->visited)
        neighbours.push_back(left);
    if (right && !right->visited)
        neighbours.push_back(right);

    if (neighbours.size())
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<> dist(0, neighbours.size() - 1);
        int index = dist(rng);
        return neighbours[index];
    }
    return nullptr;
}

std::vector<Cell *> Maze::getNeighbours(Cell *current)
{
    std::vector<Cell *> neighbours;
    if (current->i < rows - 1 && !current->walls["bottom"])
        neighbours.push_back(&grid[current->i + 1][current->j]);
    if (current->j < cols - 1 && !current->walls["right"])
        neighbours.push_back(&grid[current->i][current->j + 1]);
    if (current->i > 0 && !current->walls["top"])
        neighbours.push_back(&grid[current->i - 1][current->j]);
    if (current->j > 0 && !current->walls["left"])
        neighbours.push_back(&grid[current->i][current->j - 1]);

    return neighbours;
}

std::vector<Vertex> Maze::getVertices()
{
    std::vector<Vertex> vertices;

    for (auto row : grid)
    {
        for (auto c : row)
        {
            if (c.walls["top"])
            {
                vertices.push_back(Vertex{(float)(c.j * c.height), (float)(c.i * c.width), 255, 255, 255});
                vertices.push_back(Vertex{(float)((c.j + 1) * c.height), (float)(c.i * c.width), 255, 255, 255});
            }
            if (c.walls["bottom"])
            {
                vertices.push_back(Vertex{(float)(c.j * c.height), (float)((c.i + 1) * c.width), 255, 255, 255});
                vertices.push_back(Vertex{(float)((c.j + 1) * c.height), (float)((c.i + 1) * c.width), 255, 255, 255});
            }
            if (c.walls["left"])
            {
                vertices.push_back(Vertex{(float)(c.j * c.height), (float)(c.i * c.width), 255, 255, 255});
                vertices.push_back(Vertex{(float)(c.j * c.height), (float)((c.i + 1) * c.width), 255, 255, 255});
            }
            if (c.walls["right"])
            {
                vertices.push_back(Vertex{(float)((c.j + 1) * c.height), (float)(c.i * c.width), 255, 255, 255});
                vertices.push_back(Vertex{(float)((c.j + 1) * c.height), (float)((c.i + 1) * c.width), 255, 255, 255});
            }
        }
    }

    return vertices;
}