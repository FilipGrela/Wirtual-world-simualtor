//
// Created by Filip on 14/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SHEEP_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SHEEP_H

#include "../Animal.h"
class Sheep : public Animal {
  public:
    Sheep(Point point, World &world);
    Organism* clone() const override;

    void reproduce() override;
};

#endif // PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_SHEEP_H
