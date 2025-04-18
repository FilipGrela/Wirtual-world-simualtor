//
// Created by Filip on 18/04/2025.
//

#ifndef PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_DANDELION_H
#define PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_DANDELION_H

#include "../Plant.h"
#include "Dandelion.h"
class Dandelion : public Plant {
public:
  Dandelion(Point point, World &world)
      : Plant(point, Constants::Plant::Dandelion::Symbol,
              Constants::Plant::Dandelion::Strength,
              Constants::Plant::Initiative, world) {}

  void reproduce() override;
  void action() override;

  double getSpreadProbability() const override;

private:
  static constexpr double spreadProbability =
      Constants::Plant::Dandelion::SpreadProbability;
};

#endif // PROJEKT_1_PROGRAMOWANIE_OBIEKTOWE_DANDELION_H
