//
// Created by Filip on 12/04/2025.
//

#include "Organism.h"
#include "../world/World.h"

Organism::Organism(Point point, std::string symbol, int strength, int initiative, World &world)
        : position(point), symbol(symbol), strength(strength), initiative(initiative), age(0), world(world) {
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

int Organism::getStrength() const {
    return strength;
}

int Organism::getInitiative() const {
    return initiative;
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

std::string Organism::getSymbol() {
    return symbol;
}


void Organism::action() {
    // Pusta definicja metody
}

void Organism::collision(Organism &other) {
    // Pusta definicja metody
}

void Organism::move(Point newPosition) {
  // Jeśli pozycja jest wolna, zaktualizuj pozycję
  position = newPosition;
  // Sprawdź, czy nowa pozycja jest zajęta
  for (auto &other : world.getOrganisms()) {
    if (other.get() != this && other->getPosition() == newPosition) {
      // Wywołaj kolizję
      this->collision(*other);
    }
  }
}

void Organism::die() {
    // Pusta definicja metody
    world.removeOrganism(this);
}
