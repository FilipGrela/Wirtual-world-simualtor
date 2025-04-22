//
// Created by Filip on 12/04/2025.
//

#pragma once

#include "../Organism.h"

class Animal : public Organism {
protected:
    bool collision(Organism &other) override;
    bool fight(Organism &other);

public:
    Animal(Point point, std::string symbol, int strength, int initiative, World &world);
};
