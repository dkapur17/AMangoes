#include "collectables.hpp"
#include "random_engine.hpp"

Gem::Gem(int iVal, int jVal, int cellDimVal)
    : i(iVal), j(jVal), cellDim(cellDimVal), collected(false),
      R(255), G(255), B(0), position(glm::vec3((2 * j + 1) * cellDim / 2, (2 * i + 1) * cellDim / 2, 0.0f)) {}

Bomb::Bomb(int iVal, int jVal, int cellDimVal)
    : i(iVal), j(jVal), cellDim(cellDimVal), collected(false),
      R1(178), G1(32), B1(47), R2(0), G2(19), B2(153), R3(240), G3(248), B3(255),
      position(glm::vec3((2 * j + 1) * cellDim / 2, (2 * i + 1) * cellDim / 2, 0.0f)) {}

CollectablesContainer::CollectablesContainer(int rowsVal, int colsVal, int cellDimVal, int gemCountVal, int bombCountVal)
    : collectablesReleased(false), rows(rowsVal), cols(colsVal), cellDim(cellDimVal), gemCount(gemCountVal), bombCount(bombCountVal)
{
    for (int i = 0; i < gemCount; i++)
        gems.push_back(Gem(RandomEngine::randomInt(0, rows - 1), RandomEngine::randomInt(0, cols - 1), cellDim));

    for (int i = 0; i < bombCount; i++)
        bombs.push_back(Bomb(RandomEngine::randomInt(0, rows - 1), RandomEngine::randomInt(0, cols - 1), cellDim));
}

std::vector<Vertex> Gem::getVertices()
{
    std::vector<Vertex> vertices = {
        Vertex{0, 10, R, G, B},
        Vertex{-12, 0, R, G, B},
        Vertex{-8, -5, R, G, B},
        Vertex{8, -5, R, G, B},
        Vertex{12, 0, R, G, B},
    };
    return vertices;
}

std::vector<Vertex> Bomb::getVertices()
{
    std::vector<Vertex> vertices =
        {
            Vertex{-15, -6, R1, G1, B1},
            Vertex{15, -6, R1, G1, B1},
            Vertex{15, 6, R1, G1, B1},
            Vertex{-15, 6, R1, G1, B1},

            Vertex{-10, -10, R2, G2, B2},
            Vertex{10, -10, R2, G2, B2},
            Vertex{10, 10, R2, G2, B2},
            Vertex{-10, 10, R2, G2, B2},

            Vertex{-6, -3, R3, G3, B3},
            Vertex{6, -3, R3, G3, B3},
            Vertex{6, 3, R3, G3, B3},
            Vertex{-6, 3, R3, G3, B3},
        };
    return vertices;
}