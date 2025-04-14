//
// Created by Filip on 14/04/2025.
//

#include "Sheep.h"

Sheep::Sheep(Point point, World &world)
    : Animal(point, Constants::Animal::Sheep::Symbol,
             Constants::Animal::Sheep::Strength,
             Constants::Animal::Sheep::Initiative, world) {}

void Sheep::reproduce() {
  Point newPosition = world.getFreeSpace(position);
  if (newPosition == Point(-1, -1)) {
    return;
  }

  world.queueOrganismAddition(new Sheep(newPosition, world));
}

