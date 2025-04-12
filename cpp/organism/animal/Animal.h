//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANIMAL_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANIMAL_H


#include "../Organism.h"

class Animal : public Organism {
private:

public:
    Animal(int x, int y, char symbol, int energy, int age, int maxEnergy, int maxAge);
    ~Animal() override;

};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANIMAL_H
