//
// Created by Filip on 15/04/2025.
//

#include "Turtle.h"

Turtle::Turtle(Point point, World &world)
    : Animal(point, Constants::Animal::Turtle::Symbol,
             Constants::Animal::Turtle::Strength,
             Constants::Animal::Turtle::Initiative, world) {}

void Turtle::reproduce() {
    Point newPosition = world.getFreeSpace(position);
    if (newPosition == Point(-1, -1)) {
        return;
    }

    world.queueOrganismAddition(new Turtle(newPosition, world));
}

void Turtle::action() {
    increaseAge();
    if (rand() % 4 != 0) {// 75% szans na brak ruchu
        return;
    }

    Point newPosition = getNewPosition();
    if (world.isInBounds(newPosition)) {
        move(newPosition);
    }
}

bool Turtle::collision(Organism &attacker) {
    if (attacker.getStrength() < 5 && attacker.getSymbol() != Constants::Animal::Turtle::Symbol) {
        world.getLogger().logEvent("Żółw odpiera atak organizmu " + attacker.getSymbol());
        Point old = attacker.getPreviousPosition();
        attacker.move(old);// Napastnik wraca na poprzednie pole
    } else {
        return Animal::collision(attacker);// Domyślna logika kolizji
    }
    return false;
}

Organism *Turtle::clone() const {
    return new Turtle(*this);// Tworzy kopię obiektu za pomocą konstruktora kopiującego
}