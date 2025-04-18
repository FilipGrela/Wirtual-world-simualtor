//
// Created by Filip on 12/04/2025.
//

#include "Plant.h"

Plant::Plant(Point point, std::string symbol, int strength, int initiative,
             World &world)
    : Organism(point, symbol, strength, initiative, world) {}

void Plant::action() {
  increaseAge();
  int chance = rand() % 100;
  if (chance > Constants::Plant::Grass::SpreadProbability * 100)
    return;

  reproduce();
}
Point Plant::getNewPosition() {
  std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1),
                                   Point(-1, 0)};

  for (const auto &direction : directions) {
    Point newPosition = position + direction;

    if (world.isInBounds(newPosition) && !isOccupiedBySameType(newPosition)) {
      return newPosition;
    }
  }
  return position; // Jeśli nie znaleziono odpowiedniej pozycji
}

bool Plant::isOccupiedBySameType(const Point &newPosition) const {
  for (const auto &organism : world.getOrganisms()) {
    if (organism != nullptr && organism->getPosition() == newPosition &&
        organism->getSymbol() == this->getSymbol()) {
      return true;
    }
  }
  return false;
}

bool Plant::collision(Organism &other) { return false; }
