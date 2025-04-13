//
// Created by Filip on 12/04/2025.
//

#include "Animal.h"
#include <random>

Animal::Animal(Point point, char symbol,int strength, int initiative, World &world)
        : Organism(point, symbol, strength, world), initiative(initiative) {}

int Animal::getInitiative() const {
    return initiative;
}

void Animal::action() {

}


void Animal::collision(Organism &other) {
    if (this->getSymbol() == other.getSymbol()) {
        // Ensure `this` is an `Animal` and call `reproduce`
        if (Animal *animal = dynamic_cast<Animal *>(this)) {
            animal->reproduce();
        }
    } else {
        // Zwierzęta są różnych gatunków - walka
    }
}

void Animal::reproduce() {

    // Jeśli brak miejsca, rozmnażanie nie jest możliwe
}
