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

Point Organism::getRandomNewPosition(const std::vector<Point> &directions) const {
  std::vector<Point> availableDirections = directions;
  Point newPosition;

  int maxAttempts = availableDirections.size();
  int attempts = 0;

  while (!availableDirections.empty() && attempts < maxAttempts) {
    int index = rand() % availableDirections.size();
    newPosition = position + availableDirections[index];
    availableDirections.erase(availableDirections.begin() + index);
    attempts++;

    if (world.isInBounds(newPosition)) {
      return newPosition;
    }
  }

  return position; // Jeśli nie znaleziono odpowiedniej pozycji
}

Point Organism::getNewPosition() {
  std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0)};
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

  Point newPosition = getNewPosition();
  if (world.isInBounds(newPosition)) {
    move(newPosition);
  }
  increaseAge();
}

void Organism::collision(Organism &other) {
    // Pusta definicja metody
}

void Organism::move(Point newPosition) {


//  // DOODATKOWA LOGIKA NIE WYMAGANA MOZNA SUNĄĆ MAX 2 ZWIERZETA NA POZYCJI
//        int organismCount = 0;
//        for (auto &other : world.getOrganisms()) {
//          if (other != nullptr && other->getPosition() == newPosition) {
//            organismCount++;
//          }
//        }
//        if (organismCount >= 2) {
//          // Jeśli są już dwa organizmy, nie wykonuj ruchu
//          return;
//        }

        // Jeśli pozycja jest wolna, zaktualizuj pozycję
        position = newPosition;

        // Sprawdź, czy nowa pozycja jest zajęta i wywołaj kolizję
        for (auto &other : world.getOrganisms()) {
          if (other != nullptr && other.get() != this && other->getPosition() == newPosition) {
            this->collision(*other);
          }
        }
      }

void Organism::die() {
    // Pusta definicja metody
    world.removeOrganism(this);
}
