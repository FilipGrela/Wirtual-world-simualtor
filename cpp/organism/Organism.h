//
// Created by Filip on 12/04/2025.
//

#pragma once

#include <vector>
#include "../Constants.h"
#include "../utilities/Point.h"

class World; // Forward declaration

class Organism {
public:
    virtual ~Organism();

    // Metody abstrakcyjne`
    virtual void action();
    virtual void collision(Organism &other);

    virtual Point getPosition();
    virtual Point setPosition(Point newPosition);
    virtual std::string getSymbol();
    virtual int getAge();
    virtual int setAge(int newAge);
    virtual int increaseAge();
    virtual void reproduce() = 0;


    void die();
    int getStrength() const;
    int getInitiative() const;

protected:
    Organism(Point point, std::string symbol, int strength, int initiative, World &world);

    void move(Point newPosition);

    Point position;
    const std::string symbol;
    const int strength;
    const int initiative;
    int age;

    World &world; // Referencja do świata, w którym znajduje się organizm
};
