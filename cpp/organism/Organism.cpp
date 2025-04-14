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

void Organism::collision(Organism &other) {
    // Pusta definicja metody
}

void Organism::move(Point newPosition) {
  // Loguj próbę ruchu
  world.getLogger().logEvent("Organizm " + this->getSymbol() + " próbuje się poruszyć z pozycji " +
                             std::to_string(position.x) + "," + std::to_string(position.y) +
                             " na pozycję " + std::to_string(newPosition.x) + "," + std::to_string(newPosition.y));

  // Jeśli pozycja jest wolna, zaktualizuj pozycję
  position = newPosition;

  // Sprawdź, czy nowa pozycja jest zajęta
  for (auto &other : world.getOrganisms()) {
    if (other != nullptr && other.get() != this && other->getPosition() == newPosition) {
      // Loguj kolizję
      world.getLogger().logEvent("Kolizja: Organizm " + this->getSymbol() + " zderzył się z organizmem " +
                                 other->getSymbol() + " na pozycji " +
                                 std::to_string(newPosition.x) + "," + std::to_string(newPosition.y));
      // Wywołaj kolizję
      this->collision(*other);
    }
  }
}

void Organism::die() {
    // Pusta definicja metody
    world.removeOrganism(this);
}
