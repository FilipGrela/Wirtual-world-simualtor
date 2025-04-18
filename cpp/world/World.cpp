//
// Created by Filip on 12/04/2025.
//

#include "World.h"
#include "../Constants.h"
#include "../organism/animal/species/Human.h"
#include <algorithm>
#include <sstream>
#include <thread>

#include "../organism/plant/Plant.h"
World::World(int width, int height) : width(width), height(height) {}

void World::draw() const {
  std::ostringstream buffer; // Bufor do przechowywania całego wyniku

  for (int y = 0; y <= height - 1; y++) {
    for (int x = 0; x <= width - 1; x++) {
      Point position(x, y);
      bool found = false;
      for (const auto &organism : organisms) {
        Point organismPos = organism->getPosition();
        if (organismPos == position) {
          buffer << organism->getSymbol(); // Dodaj symbol organizmu do bufora
          found = true;
          break;
        }
      }
      if (!found) {
        buffer << Constants::World::EmptySymbol; // Dodaj pusty symbol do bufora
      }
    }
    buffer << '\n'; // Dodaj nową linię do bufora
  }

  std::cout << buffer.str(); // Wypisz cały bufor na konsolę
}
bool World::isOccupied(Point position) const {
  for (const auto &organism : organisms) {
    if (organism->getPosition() == position) {
      return true;
    }
  }
  for (const auto &organism : organismsToAdd) {
    if (organism->getPosition() == position) {
      return true;
    }
  }
  return false;
}

bool World::isInBounds(Point position) const {
  return position.x >= 0 && position.x < width && position.y >= 0 &&
         position.y < height;
}

void World::executeTurn() {

  std::sort(organisms.begin(), organisms.end(),
            [](const std::unique_ptr<Organism> &a,
               const std::unique_ptr<Organism> &b) {
              if (a->getInitiative() != b->getInitiative()) {
                return a->getInitiative() >
                       b->getInitiative(); // Wyższa inicjatywa ma pierwszeństwo
              }
              return a->getAge() >
                     b->getAge(); // Starszy organizm ma pierwszeństwo
            });

  for (auto &organism : organisms) {
    if (organism != nullptr) {
      organism->action();
    }
  }

  for (auto &newOrganism : organismsToAdd) {
    addOrganism(newOrganism.release());
  }
  organismsToAdd.clear();

  incrementTurnCounter();
}

void World::addOrganism(Organism *organism) {
  organisms.emplace_back(organism);
  if (organism->isHuman()) {
    humanAlive = true;
  }
}

/**
 * This function finds the nearest free space for the new organism to be placed
 * in the world.
 */
Point World::getFreeSpace(Point &newPosition) {
  static const std::vector<Point> directions = {
      Point(0, 1),  // Up
      Point(1, 0),  // Right
      Point(0, -1), // Down
      Point(-1, 0)  // Left
  };

  for (const auto &direction : directions) {
    Point candidate = newPosition + direction;
    if (isInBounds(candidate) && !isOccupied(candidate)) {
      return candidate;
    }
  }
  return {-1, -1}; // No free space found
}

const std::vector<std::unique_ptr<Organism>> &World::getOrganisms() const {
  return organisms;
}
const std::vector<std::unique_ptr<Organism>> &World::getOrganismsToAdd() const {
  return organismsToAdd;
}

void World::queueOrganismAddition(Organism *organism) {
  organismsToAdd.emplace_back(organism);
}

void World::removeOrganism(Organism *organism) {
  organisms.erase(
      std::remove_if(organisms.begin(), organisms.end(),
                     [organism](const std::unique_ptr<Organism> &o) {
                       return o.get() == organism;
                     }),
      organisms.end());
}

EventLogger &World::getLogger() { return eventLogger; }

bool World::isStrongerOrganismAt(Point position, int strength) const {
  for (const auto &organism : organisms) {
    if (organism->getPosition() == position &&
        organism->getStrength() > strength) {
      return true;
    }
  }
  return false;
}

int World::incrementTurnCounter() { return ++turnCounter; }

int World::getTurnCounter() const { return turnCounter; }

void World::setHumanDirection(enum Constants::Direction direction) {
  this->humanDirection = direction;
}

Constants::Direction World::getHumanDirection() const { return this->humanDirection; };

int World::getWidth() const { return width; }
int World::getHeight() const { return height; }
bool World::getHumanAlive() const {return humanAlive;}
void World::setHumanAlive(bool alive) {
  humanAlive = alive;
}

void World::activateHumanAbility() {
  for (const auto &organism : organisms) {
    if (organism->isHuman()) {
      Human *human = dynamic_cast<Human *>(organism.get());
      if (human) {
        human->activateAbility();
      }
      break;
    }
  }
}

void World::killPlantsOnPosition(Point position) {
  std::vector<Organism *> plantsToRemove;

  for (auto &organism : organisms) {
    if (!organism) continue;
    if (!organism->isPlant()) continue;
    if (organism->getPosition() != position) continue;

    plantsToRemove.push_back(organism.get());
  }

  for (auto *plant : plantsToRemove) {
    removeOrganism(plant);
  }
}
