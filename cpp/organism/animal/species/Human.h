//
// Created by Filip on 12/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H


#include "../Animal.h"

class Human : public Animal {
public:
  Human(Point point, World &world);
  void reproduce() override;
  Point getNewPosition() override;
  bool isHuman() const override;

  void die() override;
};


#endif //PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_HUMAN_H
