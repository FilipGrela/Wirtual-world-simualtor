package constants;

public class Constants {
    public enum Direction {
        NONE, UP, DOWN, LEFT, RIGHT
    }

    public static class World {
        public static final String EmptySymbol = "⚫";
    }

    public static class Animal {
        public static class Wolf {
            public static final int Strength = 9;
            public static final int Initiative = 5;
            public static final String Symbol = "🐺";
        }
        public static class Sheep {
            public static final int Strength = 4;
            public static final int Initiative = 4;
            public static final String Symbol = "🐑";
        }
        public static class Fox {
            public static final int Strength = 3;
            public static final int Initiative = 7;
            public static final String Symbol = "🦊";
        }
        public static class Turtle {
            public static final int Strength = 2;
            public static final int Initiative = 1;
            public static final String Symbol = "🐢";
        }
        public static class Antelope {
            public static final int Strength = 4;
            public static final int Initiative = 4;
            public static final String Symbol = "🦌";
        }
        public static class Human {
            public static final int Strength = 5;
            public static final int Initiative = 4;
            public static final int AbilityCooldown = 5;
            public static final int AbilityDuration = 5;
            public static final String Symbol = "👨‍🦱";
            public static final String SymbolActiveAbility = "👨🏻‍🦰";
        }
    }

    public static class Plant {
        public static final int Initiative = 0;
        public static class Grass {
            public static final int Strength = 0;
            public static final String Symbol = "🌱";
            public static final double SpreadProbability = 0.05;
        }
        public static class Dandelion {
            public static final int Strength = 0;
            public static final String Symbol = "🌼";
            public static final double SpreadProbability = 0.01;
            public static final int NumberOfTriesToSpread = 3;
        }
        public static class Guarana {
            public static final int Strength = 0;
            public static final String Symbol = "🍒";
            public static final double SpreadProbability = 0.04;
        }
        public static class Belladonna {
            public static final int Strength = 99;
            public static final String Symbol = "☠️";
            public static final double SpreadProbability = 0.02;
        }
        public static class SosnowskyHogweed {
            public static final int Strength = 10;
            public static final String Symbol = "🌿";
            public static final double SpreadProbability = 0.01;
        }
    }
}
