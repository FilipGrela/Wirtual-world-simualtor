//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H

#include <iostream>
#include <random>

class Point {

public:
    Point();
    Point(int x, int y);

    static Point generateRandomPoint(int width, int height, std::mt19937 randomEngine);

    int x;
    int y;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point operator+(const Point &other) const;
    Point operator-(const Point &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

#endif//PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_POINT_H
