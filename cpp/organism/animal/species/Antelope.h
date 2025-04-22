//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANTELOPE_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANTELOPE_H


#include "../Animal.h"

class Antelope : public Animal {
public:
  Antelope(Point point, World &world);
  void reproduce() override;
  Point getNewPosition() override;
  Organism* clone() const override;

  bool collision(Organism &other) override;
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_ANTELOPE_H
