//
// Created by Filip on 12/04/2025.
//

#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
    return !(*this == other);
}

Point Point::operator+(const Point &other) const {
    return {};
}

Point Point::operator-(const Point &other) const {
    return {};
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}