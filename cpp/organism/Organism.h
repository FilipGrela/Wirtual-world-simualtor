//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../utilities/Point.h"

class World;

class Organism {
public:
    virtual ~Organism();

    // Metody abstrakcyjne
    virtual void action();
    virtual void collision(Organism &other);

    virtual Point getPosition();
    virtual Point setPosition(Point newPosition);
    virtual char getSymbol();
    virtual int getStrength();
    virtual int getAge();
    virtual int setAge(int newAge);
    virtual int increaseAge();

protected:
    Organism(Point point, char symbol, int strength, World &world);

    void reproduce();
    void move(Point newPosition);

    Point position;
    const char symbol;
    const int strength;
    int age;

    World &world; // Referencja do świata, w którym znajduje się organizm
};
