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
  if (chance > getSpreadProbability() * 100)
    return;

  reproduce();
}
Point Plant::getNewPosition() {
  std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1),
                                   Point(-1, 0)};

  while (!directions.empty()) {
    int randomIndex = rand() % directions.size();
    Point newPosition = position + directions[randomIndex];

    if (world.isInBounds(newPosition) && !isOccupiedBySameType(newPosition)) {
      return newPosition;
    }

    directions.erase(directions.begin() +
                     randomIndex); // Usuń nieodpowiedni kierunek
  }

  return position; // Jeśli nie znaleziono odpowiedniej pozycji
}

/**
 * Sprawdza, czy dane miejsce jest zajęte przez organizm tego samego typu
 * lub zostało już zajęte w tej turze.
 *
 * @param newPosition Pozycja, która ma zostać sprawdzona.
 * @return true, jeśli pozycja jest zajęta przez organizm tego samego typu
 *         lub została zajęta w tej turze, w przeciwnym razie false.
 */
bool Plant::isOccupiedBySameType(const Point &newPosition) const {
  const auto &allOrganisms = world.getOrganisms();
  const auto &organismsToAdd = world.getOrganismsToAdd();

  for (const auto &organism : allOrganisms) {
    if (organism != nullptr && organism->getPosition() == newPosition &&
        organism->getSymbol() == this->getSymbol()) {
      return true;
    }
  }

  for (const auto &organism : organismsToAdd) {
    if (organism != nullptr && organism->getPosition() == newPosition) {
      return true;
    }
  }

  return false;
}

bool Plant::collision(Organism &other) {
  die();
  return false;
}
