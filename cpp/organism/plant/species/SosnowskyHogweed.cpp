//
// Created by fgrel on 18.04.2025.
//

#include "SosnowskyHogweed.h"
#include "../../animal/Animal.h"

Organism* SosnowskyHogweed::clone() const {
  return new SosnowskyHogweed(*this); // Tworzy kopię obiektu za pomocą konstruktora kopiującego
}

void SosnowskyHogweed::reproduce() {
  Point newPosition = getNewPosition();
  if (newPosition == position)
    return; // Ensure a new position is valid

  world.killPlantsOnPosition(newPosition);
  world.queueOrganismAddition(new SosnowskyHogweed(newPosition, world));
}

double SosnowskyHogweed::getSpreadProbability() const {
  return spreadProbability;
}

bool SosnowskyHogweed::collision(Organism &other) {
  world.getLogger().logEvent("SosnowskyHogweed has killed  " +
                              other.getSymbol() + ".");
  other.die();
  return false;
}

void SosnowskyHogweed::killNearbyAnimals() {
  std::vector<Point> neighbors = world.getNeighboringPositions(position);
  for (const Point &neighbor : neighbors) {
    std::vector<Organism *> organisms =
        world.getOrganismsAt(neighbor);
    for (const auto &organism : organisms) {
      if (organism && dynamic_cast<Animal *>(organism)) { // Sprawdź, czy to zwierzę
        world.getLogger().logEvent("Sosnowsky Hogweed zabił " + organism->getSymbol() + " na pozycji (" +
                                   std::to_string(neighbor.x) + ", " + std::to_string(neighbor.y) + ").");
        organism->die();
      }
    }
  }
}