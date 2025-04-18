//
// Created by fgrel on 18.04.2025.
//

#include "Guarana.h"

void Guarana::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.killPlantsOnPosition(newPosition);
  world.queueOrganismAddition(new Guarana(newPosition, world));
}

double Guarana::getSpreadProbability() const {
  return spreadProbability;
}