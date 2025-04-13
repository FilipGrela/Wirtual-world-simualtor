//
// Created by Filip on 12/04/2025.
//

#include "Animal.h"
#include "../../world/World.h"
#include <random>

Animal::Animal(Point point, char symbol,int strength, int initiative, World &world)
        : Organism(point, symbol, strength, world), initiative(initiative) {}

int Animal::getInitiative() const {
    return initiative;
}


void Animal::collision(Organism &other) {
    if (this->getSymbol() == other.getSymbol()) {
        // Rozmnażanie, jeśli organizmy są tego samego gatunku
        other.reproduce();
    } else {
        // Logika walki, jeśli organizmy są różnych gatunków
    }
}
