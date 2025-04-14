//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../organism/Organism.h"
#include "../utilities/Point.h"
#include "../utilities/eventLogger/EventLogger.h"
#include <memory>
#include <vector>

class Organism; // Deklaracja wstępna

class World {
public:
    World(int width, int height);
    void draw() const;

    bool isOccupied(Point position) const;
    bool isInBounds(Point position) const;

    void executeTurn();

    void addOrganism(Organism *organism);
    void removeOrganism(Organism *organism);
    const std::vector<std::unique_ptr<Organism>> &getOrganisms() const;

    Point getFreeSpace(Point &newPosition);
    EventLogger &getLogger();

    void queueOrganismAddition(Organism *organism);
    bool isStrongerOrganismAt(Point position, int strength) const;
private:
    int width, height;

    EventLogger eventLogger; // Logger do rejestrowania zdarzeń

    std::vector<std::unique_ptr<Organism>> organisms; // vector to represent the organisms in the world
    std::vector<std::unique_ptr<Organism>> organismsToAdd; // vector to represent the organisms to add to the world
};


