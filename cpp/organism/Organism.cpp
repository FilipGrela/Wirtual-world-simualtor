//
// Created by Filip on 12/04/2025.
//

#include "Organism.h"
#include "../world/World.h"
#include <algorithm>

Organism::Organism(Point point, std::string symbol, int strength,
                   int initiative, World &world)
    : position(point), symbol(symbol), strength(strength),
      initiative(initiative), age(0), world(world) {};

Organism::~Organism() {
  // Pusta definicja destruktora
}

Point Organism::getPosition() { return position; }

Point Organism::setPosition(Point newPosition) {
  position = newPosition;

  return position;
}

int Organism::getStrength() const { return strength; }

void Organism::setStrength(int strength) { this->strength = strength; }

int Organism::getInitiative() const { return initiative; }

int Organism::getAge() { return age; }

int Organism::setAge(int newAge) {
  age = newAge;
  return age;
}

int Organism::increaseAge() {
  age++;
  return age;
}

std::string Organism::getSymbol() const { return symbol; }

Point Organism::getNewPosition() {
  std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1),
                                   Point(-1, 0)};
  Point newPosition;

  int maxAttempts = directions.size(); // Maksymalna liczba prób
  int attempts = 0;

  while (!directions.empty() && attempts < maxAttempts) {
    int index = rand() % directions.size();
    newPosition = position + directions[index];
    directions.erase(directions.begin() + index); // Usuń sprawdzony kierunek
    attempts++;

    if (world.isInBounds(newPosition)) {
      return newPosition;
    }
  }

  // Jeśli nie znaleziono wolnej przestrzeni, zwróć aktualną pozycję
  return position;
}

void Organism::action() {

  increaseAge();
  Point newPosition = getNewPosition();
  move(newPosition);
}

void Organism::move(Point newPosition) {
  Point tempOldPosition = position;
  position = newPosition;

  // Sprawdź, czy nowa pozycja jest zajęta i wywołaj kolizję
  for (auto &other : world.getOrganisms()) {
    if (other != nullptr && other.get() != this &&
    other->getPosition() == newPosition) {
      if (!other->collision(*this)) {
        previousPosition = tempOldPosition;
        break;
      }
    }
  }
}

void Organism::die() {
  // Pusta definicja metody
  world.removeOrganism(this);
}

Point Organism::getPreviousPosition() const { return previousPosition; }

void Organism::changeSymbol(const std::string& newSymbol) {
  symbol = newSymbol;
}
