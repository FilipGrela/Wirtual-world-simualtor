//
// Created by Filip on 18/04/2025.
//

#include "Dandelion.h"

void Dandelion::reproduce() {
    Point newPosition = getNewPosition();
    if (newPosition == position)
        return;// Ensure a new position is valid

    world.killPlantsOnPosition(newPosition);
    world.queueOrganismAddition(new Dandelion(newPosition, world));
}

void Dandelion::action() {
    increaseAge();
    for (int i = 0; i < Constants::Plant::Dandelion::NumberOfTriesToSpread; i++) {
        int chance = rand() % 100;
        if (chance > Constants::Plant::Dandelion::SpreadProbability * 100)
            continue;
        reproduce();
    }
}

double Dandelion::getSpreadProbability() const {
    return spreadProbability;
}

Organism *Dandelion::clone() const {
    return new Dandelion(*this);// Tworzy kopię obiektu za pomocą konstruktora kopiującego
}