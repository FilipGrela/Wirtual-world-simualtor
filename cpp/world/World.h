//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WORLD_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WORLD_H

#include <memory>
#include <vector>
#include "../organism/Organism.h"

class World {
public:
    World(int width, int height);
    void draw();
    void update();
    void addOrganism(int x, int y, char symbol);
    void removeOrganism(int x, int y);
    void moveOrganism(int oldX, int oldY, int newX, int newY);

private:
    int width;
    int height;

    std::vector<std::vector<std::unique_ptr<Organism>>> organisms; // 2D vector to represent the organisms in the world
    std::unique_ptr<std::unique_ptr<char[]>[]> grid; // 2D array to represent the world grid
    // You can also use a vector of vectors or other data structures if needed
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WORLD_H
