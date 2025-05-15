package organism;

import world.World;
import organism.animal.species.*;
import organism.plant.species.*;

public class OrganismFactory {
    public static Organism createOrganism(String type, int x, int y, World world) {
        switch (type) {
            case "Wolf":
                return new Wolf(x, y, world);
            case "Sheep":
                return new Sheep(x, y, world);
            case "Fox":
                return new Fox(x, y, world);
            case "Turtle":
                return new Turtle(x, y, world);
            case "Antelope":
                return new Antelope(x, y, world);
            case "Grass":
                return new Grass(x, y, world);
            case "Dandelion":
                return new Dandelion(x, y, world);
            case "Guarana":
                return new Guarana(x, y, world);
            case "Belladonna":
                return new Belladonna(x, y, world);
            case "SosnowskyHogweed":
                return new SosnowskyHogweed(x, y, world);
            default:
                return null;
        }
    }
}
