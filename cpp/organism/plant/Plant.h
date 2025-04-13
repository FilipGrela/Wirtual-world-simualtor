//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H

#include "../Organism.h"

class Plant : public Organism {
private:

public:
    Plant(Point point, char symbol, int strength, World &world);

    void action() override;
    void collision(Organism &other) override;
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
