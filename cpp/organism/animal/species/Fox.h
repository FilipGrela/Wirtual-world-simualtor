//
// Created by Filip on 15/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_FOX_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_FOX_H

#include "../../../utilities/Point.h"
#include "../Animal.h"

class Fox : public Animal {
public:
  Fox(Point point, World &world);

  void reproduce() override;
  Point getNewPosition() override;
  Organism* clone() const override;

private:
  bool isStrongerOrganismPresent(Point position) const;
};

#endif // PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_FOX_H