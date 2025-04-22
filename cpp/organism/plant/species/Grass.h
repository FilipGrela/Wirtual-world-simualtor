//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_GRASS_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_GRASS_H


#include "../Plant.h"

class Grass : public Plant {
public:
    Grass(Point point, World &world)
        : Plant(point, Constants::Plant::Grass::Symbol,
                Constants::Plant::Grass::Strength,
                Constants::Plant::Initiative, world) {}

    void reproduce() override;
    Organism *clone() const override;
    double getSpreadProbability() const override;

private:
    static constexpr double spreadProbability =
            Constants::Plant::Grass::SpreadProbability;
};


#endif//PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_GRASS_H
