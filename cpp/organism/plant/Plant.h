//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H

#include "../Organism.h"

class Plant : public Organism {
private:

public:
    Plant(int x, int y, char symbol, int energy, int age, int maxEnergy, int maxAge);
    ~Plant() override;

};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_PLANT_H
