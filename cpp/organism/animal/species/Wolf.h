//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WOLF_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WOLF_H


#include "../Animal.h"

class Wolf : public Animal {
public:
    Wolf(Point point, World &world);

    void action() override;
    void reproduce() override;
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_WOLF_H
