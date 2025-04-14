//
// Created by Filip on 12/04/2025.
//

#include "Wolf.h"

Wolf::Wolf(Point point, World &world)
    : Animal(point, Constants::Animal::Wolf::Symbol,
             Constants::Animal::Wolf::Strength,
             Constants::Animal::Wolf::Initiative, world) {}

void Wolf::reproduce() {
  Point newPosition = world.getFreeSpace(position);
  if (newPosition == Point(-1, -1)) {
    return;
  }

  world.queueOrganismAddition(new Wolf(newPosition, world));
}