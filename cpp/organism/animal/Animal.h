//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    const int initiative;

    void action() override;
    void collision(Organism &other) override;
public:
    Animal(Point point, char symbol, int strength, int initiative, World &world);
    int getInitiative() const;

    void reproduce();



};

