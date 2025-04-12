//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H

#include <iostream>

class Point {
    int x;
    int y;

public:
    Point(int x, int y);

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H
