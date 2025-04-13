//
// Created by Filip on 12/04/2025.
//

#pragma once

#include <memory>
#include <vector>
#include "../utilities/Point.h"
#include "../organism/Organism.h"

class Animal; // Deklaracja wstępna

class World {
public:
    World(int width, int height);
    void draw();
    void update();

    int isOccupied(Point position) const;
    bool isInBounds(Point position) const;

private:
    int width;
    int height;

    std::vector<std::unique_ptr<Organism>> organisms; // vector to represent the organisms in the world
};


