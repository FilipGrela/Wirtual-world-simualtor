//
// Created by fgrel on 18.04.2025.
//

#ifndef Belladonna_H
#define Belladonna_H

#include "../Plant.h"

class Belladonna : public Plant {
public:
  Belladonna(Point point, World &world)
          : Plant(point, Constants::Plant::Belladonna::Symbol,
                  Constants::Plant::Belladonna::Strength,
                  Constants::Plant::Initiative, world) {}

  void reproduce() override;
  double getSpreadProbability() const override;
  bool collision(Organism &other) override;

private:
  static constexpr double spreadProbability =
      Constants::Plant::Belladonna::SpreadProbability;
};



#endif //Belladonna_H
