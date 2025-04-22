//
// Created by fgrel on 18.04.2025.
//

#include "Belladonna.h"

void Belladonna::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.killPlantsOnPosition(newPosition);
  world.queueOrganismAddition(new Belladonna(newPosition, world));
}

double Belladonna::getSpreadProbability() const {
  return spreadProbability;
}

bool Belladonna::collision(Organism &other) {
  world.getLogger().logEvent("Belladonna has killed  " +
                              other.getSymbol() + ".");
  other.die();
  return false;
}

Organism* Belladonna::clone() const {
    return new Belladonna(*this); // Tworzy kopię obiektu za pomocą konstruktora kopiującego
}