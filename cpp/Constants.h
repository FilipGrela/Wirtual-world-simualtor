#pragma once

namespace Constants {
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };
struct World {
  static constexpr const char *EmptySymbol = "⚫";
};

struct Animal {
  struct Wolf {
    static constexpr int Strength = 9;
    static constexpr int Initiative = 5;
    static constexpr const char *Symbol = "🐺";
  };

  struct Sheep {
    static constexpr int Strength = 4;
    static constexpr int Initiative = 4;
    static constexpr const char *Symbol = "🐑";
  };

  struct Fox {
    static constexpr int Strength = 3;
    static constexpr int Initiative = 7;
    static constexpr const char *Symbol = "🦊";
  };

  struct Turtle {
    static constexpr int Strength = 2;
    static constexpr int Initiative = 1;
    static constexpr const char *Symbol = "🐢";
  };

  struct Antelope {
    static constexpr int Strength = 4;
    static constexpr int Initiative = 4;
    static constexpr const char *Symbol = "🦌";
  };

  struct Human {
    static constexpr int Strength = 5;
    static constexpr int Initiative = 4;
    static constexpr int AbilityCooldown = 5;
    static constexpr const char *Symbol = "👨‍🦱";
    static constexpr const char *SymbolActiveAbility = "👨🏿‍🦰";
  };
};
struct Plant {
  static constexpr int Initiative = 0;
  struct Grass {
    static constexpr int Strength = 0;
    static constexpr const char *Symbol = "🌱";
    static constexpr double SpreadProbability = 0.05;
  };

  struct Dandelion {
    static constexpr int Strength = 0;
    static constexpr const char *Symbol = "🌼";
    static constexpr double SpreadProbability = 0.01;
    static constexpr int NumberOfTriesToSpread = 3;
  };

  struct Guarana {
    static constexpr int Strength = 0;
    static constexpr const char *Symbol = "🍒";
    static constexpr double SpreadProbability = 0.04;
  };

  struct Belladonna {
    static constexpr int Strength = 99;
    static constexpr const char *Symbol = "☠️";
    static constexpr double SpreadProbability = 0.02;
  };

  struct SosnowskyHogweed {
    static constexpr int Strength = 10;
    static constexpr const char *Symbol = "🌿";
    static constexpr double SpreadProbability = 0.01;
  };
};
} // namespace Constants