//
// Created by fgrel on 18.04.2025.
//

#ifndef GUARANA_H
#define GUARANA_H

#include "../Plant.h"

class Guarana : public Plant {
public:
    Guarana(Point point, World &world)
        : Plant(point, Constants::Plant::Guarana::Symbol,
                Constants::Plant::Guarana::Strength, Constants::Plant::Initiative,
                world) {}

    Organism *clone() const override;
    void reproduce() override;
    double getSpreadProbability() const override;
    bool collision(Organism &other) override;

private:
    static constexpr double spreadProbability =
            Constants::Plant::Guarana::SpreadProbability;
};

#endif// GUARANA_H
