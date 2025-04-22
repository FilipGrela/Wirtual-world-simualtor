//
// Created by Filip on 12/04/2025.
//

#include "Point.h"
#include <random>


Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
    return !(*this == other);
}

Point Point::operator+(const Point &other) const {
    return {x + other.x, y + other.y};
}

Point Point::operator-(const Point &other) const {
    return {x - other.x, y - other.y};
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

Point Point::generateRandomPoint(int width, int height, std::mt19937 randomEngine) {
    std::uniform_int_distribution<> distX(0, width - 1);
    std::uniform_int_distribution<> distY(0, height - 1);

    int randomX = distX(randomEngine);
    int randomY = distY(randomEngine);
    return Point(randomX, randomY);
}
