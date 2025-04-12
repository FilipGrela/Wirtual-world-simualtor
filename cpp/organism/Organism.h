//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ORGANISM_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ORGANISM_H

#include "../utilities/Point.h"

class Organism {
    virtual ~Organism() = default;

    // Metody czysto abstrakcyjne
    virtual void action() = 0;
    virtual void collision(Organism &other) = 0;
    virtual char draw() const = 0;
public:
private:
    Point position;
    char symbol;
    int energy;
    int age;
    int maxEnergy;
    int maxAge;
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ORGANISM_H
