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
    void draw() const;
    void update();

    bool isOccupied(Point position) const;
    bool isInBounds(Point position) const;

    void executeTurn();

    void addOrganism(Organism *organism);

    const std::vector<std::unique_ptr<Organism>> &getOrganisms() const;

    Point getFreeSpace(Point &newPosition);

    void queueOrganismAddition(Organism *organism);

private:
    int width, height;

    std::vector<std::unique_ptr<Organism>> organisms; // vector to represent the organisms in the world
    std::vector<std::unique_ptr<Organism>> organismsToAdd; // vector to represent the organisms to add to the world
};


