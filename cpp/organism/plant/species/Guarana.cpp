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

bool Guarana::collision(Organism &other) {
  other.setStrength(other.getStrength() + 3);
  world.getLogger().logEvent("Guarana has increased the strength of " +
                              other.getSymbol() + " by 3.");
  die();
  return false;
}

Organism* Guarana::clone() const {
    return new Guarana(*this); // Tworzy kopię obiektu za pomocą konstruktora kopiującego
}