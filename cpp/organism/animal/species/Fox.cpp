//
// Created by Filip on 15/04/2025.
//

#include "Fox.h"

Fox::Fox(Point point, World &world)
    : Animal(point, Constants::Animal::Fox::Symbol,
             Constants::Animal::Fox::Strength,
             Constants::Animal::Fox::Initiative, world) {}
void Fox::reproduce() {
    Point newPosition = world.getFreeSpace(position);
    if (newPosition == Point(-1, -1)) {
        return;
    }

    world.queueOrganismAddition(new Fox(newPosition, world));
}

Point Fox::getNewPosition() {
   std::vector<Point> directions = {Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0), Point(1, 1), Point(1, -1), Point(-1, 1), Point(-1, -1)};
    Point newPosition;

    int maxAttempts = directions.size();// Maksymalna liczba prób
    int attempts = 0;

    while (!directions.empty() && attempts < maxAttempts) {
        int index = rand() % directions.size();
        newPosition = position + directions[index];
        directions.erase(directions.begin() + index);// Usuń sprawdzony kierunek
        attempts++;

        if (world.isInBounds(newPosition) && !isStrongerOrganismPresent(newPosition)) {
            return newPosition;
        }
    }

    // Jeśli nie znaleziono odpowiedniego pola, zwróć aktualną pozycję
    return position;
}
// Fox.cpp
bool Fox::isStrongerOrganismPresent(Point position) const {
    return world.isStrongerOrganismAt(position, this->getStrength());
}
Organism *Fox::clone() const {
    return new Fox(*this);// Tworzy kopię obiektu za pomocą konstruktora kopiującego
}