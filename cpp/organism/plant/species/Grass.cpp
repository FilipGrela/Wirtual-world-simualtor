//
// Created by Filip on 12/04/2025.
//

#include "Grass.h"

void Grass::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.killPlantsOnPosition(newPosition);
  world.queueOrganismAddition(new Grass(newPosition, world));
}

double Grass::getSpreadProbability() const {
  return spreadProbability;
}

Organism* Grass::clone() const {
    return new Grass(*this); // Tworzy kopię obiektu za pomocą konstruktora kopiującego
}