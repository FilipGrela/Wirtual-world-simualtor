//
// Created by fgrel on 18.04.2025.
//

#ifndef SosnowskyHogweed_H
#define SosnowskyHogweed_H

#include "../Plant.h"

class SosnowskyHogweed : public Plant {
public:
  SosnowskyHogweed(Point point, World &world)
          : Plant(point, Constants::Plant::SosnowskyHogweed::Symbol,
                  Constants::Plant::SosnowskyHogweed::Strength,
                  Constants::Plant::Initiative, world) {}
  Organism* clone() const override;

  void reproduce() override;
  double getSpreadProbability() const override;
  bool collision(Organism &other) override;
  bool isSosnowskyHogweed() const override { return true; }
  void killNearbyAnimals();

private:
  static constexpr double spreadProbability =
      Constants::Plant::SosnowskyHogweed::SpreadProbability;
};



#endif //SosnowskyHogweed_H
