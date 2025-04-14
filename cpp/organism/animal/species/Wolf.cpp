//
// Created by Filip on 12/04/2025.
//

#include "Wolf.h"
#include "../../../world/World.h"
#include <cstdlib>

Wolf::Wolf(Point point, World &world)
        : Animal(point, Constants::Animal::Wolf::Symbol, Constants::Animal::Wolf::Strength, Constants::Animal::Wolf::Initiative, world) {}

void Wolf::action() {

    Point directions[] = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
    Point newPosition;

    int maxAttempts = 25; // Maksymalna liczba prób
    int attempts = 0;
    do {
        newPosition = position + directions[rand() % 4];
        attempts++;
    } while (!world.isInBounds(newPosition) && attempts < maxAttempts);

    if (attempts >= maxAttempts) {
        return; // Nie znaleziono wolnej przestrzeni
    }

    move(newPosition);
}

void Wolf::reproduce() {
    Point newPosition = world.getFreeSpace(position);
    if (newPosition == Point(-1, -1)) {
        return;
    }

    world.queueOrganismAddition(new Wolf(newPosition, world));
}