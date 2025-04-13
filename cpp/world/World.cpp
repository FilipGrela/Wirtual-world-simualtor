//
// Created by Filip on 12/04/2025.
//

#include "World.h"

World::World(int width, int height) : width(width), height(height) {}

int World::isOccupied(Point position) const {
    return 0;
}

bool World::isInBounds(Point position) const {
    return position.x >= 0 && position.x < width &&
           position.y >= 0 && position.y < height;
}

