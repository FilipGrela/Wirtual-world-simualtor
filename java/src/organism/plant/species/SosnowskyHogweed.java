package organism.plant.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.animal.Animal;
import organism.plant.Plant;
import world.World;

import java.util.List;

public class SosnowskyHogweed extends Plant {

    public SosnowskyHogweed(int x, int y, World world) {
        super(x, y, Constants.Plant.SosnowskyHogweed.Symbol, Constants.Plant.SosnowskyHogweed.Strength, Constants.Plant.Initiative, world);
    }

    @Override
    public void action() {
        increaseAge();
        killNearbyAnimals();
        if (Math.random() <= getSpreadProbability()) {
            reproduce();
        }
    }

    @Override
    protected void reproduce() {
        int[] newPosition = getNewPosition();
        if (newPosition[0] == x && newPosition[1] == y) return;
        world.addOrganism(new SosnowskyHogweed(newPosition[0], newPosition[1], world));
        EventLogger.getInstance().log("Sosnowsky Hogweed spread to (" + newPosition[0] + ", " + newPosition[1] + ")");
    }

    @Override
    protected double getSpreadProbability() {
        return Constants.Plant.SosnowskyHogweed.SpreadProbability;
    }

    @Override
    public boolean collision(Organism other) {
        EventLogger.getInstance().log("Sosnowsky Hogweed has killed " + other.getClass().getName() + " at (" + x + ", " + y + ")");
        other.die();
        return false;
    }

    private void killNearbyAnimals() {
        List<int[]> neighbors = world.getNeighbors(x, y);
        for (int[] pos : neighbors) {
            Organism org = world.getOrganismAt(pos[0], pos[1]);
            if (org instanceof Animal) {
                EventLogger.getInstance().log("Sosnowsky Hogweed killed " + org.getClass().getName() + " at (" + pos[0] + ", " + pos[1] + ")");
                org.die();
            }
        }
    }
}