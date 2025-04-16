//
// Created by Filip on 12/04/2025.
//

#include "Human.h"

Human::Human(Point point, World &world)
    : Animal(point, Constants::Animal::Human::Symbol,
             Constants::Animal::Human::Strength,
             Constants::Animal::Human::Initiative, world) {}

void Human::reproduce() {
  Point newPosition = world.getFreeSpace(position);
  if (newPosition == Point(-1, -1)) {
    return;
  }

  world.queueOrganismAddition(new Human(newPosition, world));
}

Point Human::getNewPosition() {
  Constants::Direction direction = world.getHumanDirection();
  Point newPosition = position + world.directionToPoint[direction];

  if (world.isInBounds(newPosition)){
    return newPosition;
  }
  return position;
}