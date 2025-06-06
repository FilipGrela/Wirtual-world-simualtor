//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H

#include "../Organism.h"

class Plant : public Organism {
private:
public:
    Plant(Point point, std::string symbol, int strength, int initiative,
          World &world);

    void action() override;
    bool collision(Organism &other) override;

    Point getNewPosition() override;
    bool isPlant() const override { return true; }
    bool isOccupiedBySameType(const Point &newPosition) const;
    virtual double getSpreadProbability() const = 0;
};

#endif// PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
