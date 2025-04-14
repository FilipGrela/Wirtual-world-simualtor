//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    void collision(Organism &other) override;
public:
    Animal(Point point, std::string symbol, int strength, int initiative, World &world);

};

