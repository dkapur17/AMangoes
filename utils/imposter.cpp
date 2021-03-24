#include "imposter.hpp"
#include <cstdlib>

Imposter::Imposter(float stepSizeVal, int rBody, int gBody, int bBody, int rGlass, int gGlass, int bGlass, int rows, int cols)
    : stepSize(stepSizeVal), Rb(rBody), Gb(gBody), Bb(bBody), Rg(rGlass), Gg(gGlass), Bg(bGlass)
{
    srand(time(0));
    i = rand() % rows;
    j = rand() % cols;

    position = glm::vec3((2 * j + 1) * stepSize / 2, (2 * i + 1) * stepSize / 2, 0);
}
void Imposter::Move(char dir, float dt) {}

std::vector<Vertex> Imposter::getVertices()
{
    std::vector<Vertex> vertices =
        {
            // Body
            Vertex{0.6, -0.5, Rb, Gb, Bb},
            Vertex{0.6, 0.7, Rb, Gb, Bb},
            Vertex{-0.6, 0.7, Rb, Gb, Bb},
            Vertex{-0.6, -0.5, Rb, Gb, Bb},
            // Right Leg
            Vertex{0.6, 0.5, Rb, Gb, Bb},
            Vertex{0.6, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 1.0, Rb, Gb, Bb},
            Vertex{0.2, 0.25, Rb, Gb, Bb},
            // Left Leg
            Vertex{-0.6, 0.5, Rb, Gb, Bb},
            Vertex{-0.6, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 1.0, Rb, Gb, Bb},
            Vertex{-0.2, 0.25, Rb, Gb, Bb},
        };
    // Head
    for (float x = -0.6; x <= 0.61; x += 0.012)
    {
        float y = -(sqrt((0.5 * 0.5) * (std::max((0.60 * 0.60) - (x * x), 0.0)) / (0.60 * 0.60)) + 0.5);
        vertices.push_back(Vertex{x, y, Rb, Gb, Bb});
    }
    // Glasses
    vertices.push_back(Vertex{-0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back(Vertex{0.4, -0.60, Rg, Gg, Bg});
    vertices.push_back(Vertex{0.4, 0, Rg, Gg, Bg});
    vertices.push_back(Vertex{-0.4, 0, Rg, Gg, Bg});

    return vertices;
}

void Imposter::computeStep(Maze maze, Player player) {}