//
// Created by Filip on 12/04/2025.
//

#include "Human.h"
#include <random>

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


bool Human::isHuman() const { return true; }

void Human::die() {
  // Pusta definicja metody
  world.setHumanAlive(false);
  Organism::die();
}

void Human::activateAbility() {
  if (abilityCooldown == 0 && !isAbilityActive) {
    changeSymbol(Constants::Animal::Human::SymbolActiveAbility);
    isAbilityActive = true;  // Aktywuj umiejętność
    abilityDuration = 5;     // Ustaw czas trwania na 5 tur
    std::cout << "Specjalna umiejętność została aktywowana!" << std::endl;
  } else if (abilityCooldown > 0) {
    std::cout << "Umiejętność jest na cooldownie przez " << abilityCooldown
              << " tur." << std::endl;
  } else {
    std::cout << "Umiejętność jest już aktywna!" << std::endl;
  }
}

void Human::action() {
  if (isAbilityActive) {
    // Umiejętność aktywna
    abilityDuration--;
    if (abilityDuration == 0) {
      // TODO odkomentować to
//      changeSymbol(Constants::Animal::Human::Symbol);
//      isAbilityActive = false; // Dezaktywuj umiejętność
      abilityCooldown = 5;     // Ustaw cooldown na 5 tur
      std::cout << "Specjalna umiejętność została dezaktywowana!" << std::endl;
    }
  } else if (abilityCooldown > 0) {
    // Odliczanie cooldownu
    abilityCooldown--;
  }

  Animal::action();
}

void Human::escapeToRandomPosition() {
  static const std::vector<Point> directions = {
      Point(0, 1),  // Góra
      Point(1, 0),  // Prawo
      Point(0, -1), // Dół
      Point(-1, 0)  // Lewo
  };

  std::vector<Point> possiblePositions;
  for (const auto &direction : directions) {
    Point candidate = position + direction;
    if (world.isInBounds(candidate) && !world.isOccupied(candidate)) {
      possiblePositions.push_back(candidate);
    }
  }

  if (!possiblePositions.empty()) {
    // Losowe wybieranie nowej pozycji
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, possiblePositions.size() - 1);
    Point newPosition = possiblePositions[dis(gen)];

    move(newPosition);
    std::cout << "Człowiek unika śmierci i ucieka na nowe pole!" << std::endl;
  } else {
    std::cout << "Człowiek nie ma gdzie uciec, pozostaje na miejscu!" << std::endl;
  }
}


bool Human::collision(Organism &other) {
  if (isAbilityActive) {
    escapeToRandomPosition();
    return false; // Uniknięcie kolizji
  }

  // Standardowe zachowanie
  return Animal::collision(other);
}