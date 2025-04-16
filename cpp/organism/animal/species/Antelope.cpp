//
// Created by Filip on 12/04/2025.
//

#include "Antelope.h"

Antelope::Antelope(Point point, World &world)
    : Animal(point, Constants::Animal::Antelope::Symbol,
             Constants::Animal::Antelope::Strength,
             Constants::Animal::Antelope::Initiative, world) {}

void Antelope::reproduce() {
  Point newPosition = world.getFreeSpace(position);
  if (newPosition == Point(-1, -1)) {
    return;
  }

  world.queueOrganismAddition(new Antelope(newPosition, world));
}

Point Antelope::getNewPosition() {
  std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0),
                                   Point(0, 2), Point(2, 0), Point(0, -2), Point(-2, 0)};
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

bool Antelope::collision(Organism &attacker) {
  if (rand() % 2 == 0) {
    // TODO log ucieczka przed walką
    move(getNewPosition());
  } else {
    return  Animal::collision(attacker); // Domyślna logika kolizji
  }
  return true;
}
