//
// Created by Filip on 12/04/2025.
//

#include "Grass.h"

void Grass::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.addOrganism(new Grass(newPosition, world));
}