package constants;

public class Constants {
    public enum Direction {
        NONE, UP, DOWN, LEFT, RIGHT
    }

    public static final int logNotifyInterval = 100; // ms

    public static class Map {
        public static class Chessboard{
            public static final int DefaultWidth = 20;
            public static final int DefaultHeight = 20;
        }
     }

    public static class Dialog {
        public static String[] OrganismToAdd = {
                "Wolf", "Sheep", "Fox", "Turtle",
                "Antelope", "Grass", "Dandelion", "Guarana",
                "Belladonna", "SosnowskyHogweed"};
    }


    public static class Animal {
        public static class Wolf {
            public static final int Strength = 9;
            public static final int Initiative = 5;
            public static final String Symbol = "/icons/wolf.png";
        }
        public static class Sheep {
            public static final int Strength = 4;
            public static final int Initiative = 4;
            public static final String Symbol = "/icons/sheep.png";
        }
        public static class Fox {
            public static final int Strength = 3;
            public static final int Initiative = 7;
            public static final String Symbol = "/icons/fox.png";
        }
        public static class Turtle {
            public static final int Strength = 2;
            public static final int Initiative = 1;
            public static final String Symbol = "/icons/turtle.png";
        }
        public static class Antelope {
            public static final int Strength = 4;
            public static final int Initiative = 4;
            public static final String Symbol = "/icons/antelope.png";
        }
        public static class Human {
            public static final int Strength = 5;
            public static final int Initiative = 4;
            public static final int AbilityCooldown = 5;
            public static final int AbilityDuration = 5;
            public static final String Symbol = "/icons/human.png";
            public static final String SymbolActiveAbility = "/icons/human-active.png";
        }
    }

    public static class Plant {
        public static final int Initiative = 0;
        public static class Grass {
            public static final int Strength = 0;
            public static final String Symbol = "/icons/grass.png";
            public static final double SpreadProbability = 0.05;
        }
        public static class Dandelion {
            public static final int Strength = 0;
            public static final String Symbol = "/icons/dandelion.png";
            public static final double SpreadProbability = 0.01;
            public static final int NumberOfTriesToSpread = 3;
        }
        public static class Guarana {
            public static final int Strength = 0;
            public static final String Symbol = "/icons/guarana.png";
            public static final double SpreadProbability = 0.04;
        }
        public static class Belladonna {
            public static final int Strength = 99;
            public static final String Symbol = "/icons/belladonna.png";
            public static final double SpreadProbability = 0.02;
        }
        public static class SosnowskyHogweed {
            public static final int Strength = 10;
            public static final String Symbol = "/icons/sosnowsky-hogweed.png";
            public static final double SpreadProbability = 0.01;
        }
    }
}
