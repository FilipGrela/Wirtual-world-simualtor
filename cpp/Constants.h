#pragma once

namespace Constants {
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
    };
}