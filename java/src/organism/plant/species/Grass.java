package organism.plant.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.plant.Plant;
import world.World;

public class Grass extends Plant {

    public Grass(int x, int y, World world) {
        super(x, y, Constants.Plant.Grass.Symbol, Constants.Plant.Grass.Strength, Constants.Plant.Initiative, world);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = getNewPosition();
        if (newPosition[0] == x && newPosition[1] == y) return;
        world.addOrganism(new Grass(newPosition[0], newPosition[1], world));
        EventLogger.getInstance().log("Grass spread to (" + newPosition[0] + ", " + newPosition[1] + ")");
    }

    @Override
    protected double getSpreadProbability() {
        return Constants.Plant.Grass.SpreadProbability;
    }
}