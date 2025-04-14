//
// Created by Filip on 12/04/2025.
//

#include "Animal.h"
#include "../../world/World.h"
#include <random>
#include <utility>

Animal::Animal(Point point, std::string symbol,int strength, int initiative, World &world)
        : Organism(point, std::move(symbol), strength, initiative, world){}


void Animal::collision(Organism &other) {
    if (this->getSymbol() == other.getSymbol()) {
        // Rozmnażanie, jeśli organizmy są tego samego gatunku
        other.reproduce();
    } else {
        // Logika walki, jeśli organizmy są różnych gatunków
    }
}
