//
// Created by Filip on 12/04/2025.
//

#include "Grass.h"

void Grass::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.killPlantOnPosition(newPosition);
  world.queueOrganismAddition(new Grass(newPosition, world));
}

double Grass::getSpreadProbability() const {
  return spreadProbability;
}