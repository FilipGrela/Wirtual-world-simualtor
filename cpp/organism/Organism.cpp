//
// Created by Filip on 12/04/2025.
//

#include "Organism.h"

Organism::Organism(Point point, char symbol, int strength, World &world)
        : position(point), symbol(symbol), strength(strength), age(0), world(world) {
};

Organism::~Organism() {
    // Pusta definicja destruktora
}

Point Organism::getPosition() {
    return position;
}

Point Organism::setPosition(Point newPosition) {
    position = newPosition;

    return position;
}

int Organism::getStrength() {
    return strength;
}

int Organism::getAge() {
    return age;
}

int Organism::setAge(int newAge) {
    age = newAge;
    return age;
}

int Organism::increaseAge() {
    age++;
    return age;
}

char Organism::getSymbol() {
    return symbol;
}


void Organism::action() {
    // Pusta definicja metody
}

void Organism::collision(Organism &other) {
    // Pusta definicja metody
}
