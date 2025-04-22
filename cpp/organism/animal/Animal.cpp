//
// Created by Filip on 12/04/2025.
//

#include "Animal.h"
#include "../../world/World.h"
#include <random>
#include <utility>

Animal::Animal(Point point, std::string symbol, int strength, int initiative,
               World &world)
    : Organism(point, std::move(symbol), strength, initiative, world) {}

bool Animal::collision(Organism &other) {
  if (this->getSymbol() == other.getSymbol()) {
    // Rozmnażanie, jeśli organizmy są tego samego gatunku
    reproduce();
  } else {
    // Logika walki, jeśli organizmy są różnych gatunków
    return !fight(other);
  }
  return false;
}

bool Animal::fight(Organism &other) {
  // Pusta definicja metody
  if (this->getStrength() < other.getStrength()) {
    world.getLogger().logEvent(
        "Organizm " + this->getSymbol() + " został pokonany przez " +
        other.getSymbol());
    die();
    return true;
  }

  world.getLogger().logEvent(
      "Organizm " + this->getSymbol() + " pokonał " + other.getSymbol());
  other.die();
  return false;

}
