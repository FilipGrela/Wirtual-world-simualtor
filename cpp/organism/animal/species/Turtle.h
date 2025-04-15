//
// Created by Filip on 15/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_TURTLE_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_TURTLE_H

#include "../Animal.h"
class Turtle : public Animal {
public:
  Turtle(Point point, World &world);

  void reproduce() override;
  bool collision(Organism &other) override;

  void action() override;
};

#endif // PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_TURTLE_H
