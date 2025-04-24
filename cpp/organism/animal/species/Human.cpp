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

    if (world.isInBounds(newPosition)) {
        return newPosition;
    }
    return position;
}


bool Human::isHuman() const { return true; }

void Human::die() {
    if (abilityActive) {
        escapeToRandomPosition();
        world.getLogger().logEvent("Człowiek unika śmierci dzięki specjalnej umiejętności!");
        return;// Uniknięcie śmierci
    }

    // Standardowe zachowanie w przypadku śmierci
    world.setHumanAlive(false);
    Organism::die();
}

void Human::activateAbility() {
    if (abilityCooldown == 0 && !abilityActive) {
        changeSymbol(Constants::Animal::Human::SymbolActiveAbility);
        abilityActive = true;                                     // Aktywuj umiejętność
        abilityDuration = Constants::Animal::Human::AbilityDuration;// Ustaw czas trwania na 5 tur
        world.getLogger().logEvent("Specjalna umiejętność została aktywowana!");
    } else if (abilityCooldown >= 0) {

        world.getLogger().logEvent("Umiejętność jest na cooldownie przez " + std::to_string(abilityCooldown) + " tur.");
    } else {
        world.getLogger().logEvent("Umiejętność jest już aktywna!");
    }
}

void Human::action() {
    if (abilityActive) {
        // Umiejętność aktywna
        abilityDuration--;
        if (abilityDuration < 0) {
            changeSymbol(Constants::Animal::Human::Symbol);
            abilityActive = false;                                    // Dezaktywuj umiejętność
            abilityCooldown = Constants::Animal::Human::AbilityCooldown;// Ustaw cooldown na 5 tur
            world.getLogger().logEvent("Specjalna umiejętność została dezaktywowana!");
        }
    } else if (abilityCooldown > 0) {
        // Odliczanie cooldownu
        abilityCooldown--;
    }

    Animal::action();
}

void Human::escapeToRandomPosition() {
    static const std::vector<Point> directions = {
            Point(0, 1), // Góra
            Point(1, 0), // Prawo
            Point(0, -1),// Dół
            Point(-1, 0) // Lewo
    };

    std::vector<Point> possiblePositions;
    for (const auto &direction: directions) {
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
        world.getLogger().logEvent("Człowiek unika śmierci i ucieka na nowe pole!");
    } else {
        world.getLogger().logEvent("Człowiek nie ma gdzie uciec, pozostaje na miejscu!");
    }
}

Organism *Human::clone() const {
    return new Human(*this);// Tworzy kopię obiektu za pomocą konstruktora kopiującego
}
void Human::setAbilityCooldown(int cooldown) {
    this->abilityCooldown = cooldown;
}

void Human::setAbilityDuration(int duration) {
    this->abilityDuration = duration;
}

int Human::getAbilityCooldown() const {
    return abilityCooldown;
}

void Human::setAbilityActive(bool active) {
    this->abilityActive = active;
}

int Human::getAbilityDuration() const {
    return abilityDuration;
}
int Human::getAbilityyCooldown() const {
    return abilityCooldown;
}
bool Human::isAbilityActive() const {
    return abilityActive;
}
