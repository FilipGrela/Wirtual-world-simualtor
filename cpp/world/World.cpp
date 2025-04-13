//
// Created by Filip on 12/04/2025.
//

#include <thread>
#include "World.h"

World::World(int width, int height) : width(width), height(height) {}

void World::draw() const {
    for (int y = 0; y <= height-1; y++) {
        for (int x = 0; x <= width-1; x++) {
            Point position(x, y);
            bool found = false;
            for (const auto &organism : organisms) {
                Point organismPos = organism->getPosition();
                if (organismPos == position) {
                    std::cout << organism->getSymbol();
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << ".";
            }
//            std::cout << "(" << x << "," << y << ") ";
        }
        std::cout << std::endl;
    }
}
bool World::isOccupied(Point position) const {
    for (const auto &organism : organisms) {
        if (organism->getPosition() == position) {
            return true;
        }
    }
    return false;
}

bool World::isInBounds(Point position) const {
    return position.x >= 0 && position.x < width &&
           position.y >= 0 && position.y < height;
}

void World::executeTurn() {

    for (auto &organism : organisms) {
        if (organism) {
            organism->action();
        }
    }

    for (auto &newOrganism : organismsToAdd) {
        addOrganism(newOrganism.release());
    }
    organismsToAdd.clear();
}

void World::addOrganism(Organism *organism) {
    organisms.emplace_back(organism);
}

/**
 * This function finds the nearest free space for the new organism to be placed in the world.
 */
Point World::getFreeSpace(Point &newPosition) {
    static const std::vector<Point> directions = {
            Point(0, 1),  // Up
            Point(1, 0),  // Right
            Point(0, -1), // Down
            Point(-1, 0)  // Left
    };

    for (const auto &direction : directions) {
        Point candidate = newPosition + direction;
        if (isInBounds(candidate) && !isOccupied(candidate)) {
            return candidate;
        }
    }
    return {-1, -1}; // No free space found
}

const std::vector<std::unique_ptr<Organism>> &World::getOrganisms() const {
    return organisms;
}

void World::queueOrganismAddition(Organism *organism) {
    organismsToAdd.emplace_back(organism);
}