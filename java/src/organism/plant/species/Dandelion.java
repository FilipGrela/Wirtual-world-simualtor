package organism.plant.species;

import constants.Constants;
import logger.EventLogger;
import organism.plant.Plant;
import world.World;

public class Dandelion extends Plant {

    public Dandelion(int x, int y, World world) {
        super(x, y, Constants.Plant.Dandelion.Symbol, Constants.Plant.Dandelion.Strength, Constants.Plant.Initiative, world);
    }

    @Override
    public void action() {
        increaseAge();
        for (int i = 0; i < Constants.Plant.Dandelion.NumberOfTriesToSpread; i++) {
            if (Math.random() <= Constants.Plant.Dandelion.SpreadProbability) {
                reproduce();
            }
        }
    }

    @Override
    protected void reproduce() {
        int[] newPosition = getNewPosition();
        if (newPosition[0] == x && newPosition[1] == y) return;
        world.addOrganism(new Dandelion(newPosition[0], newPosition[1], world));
        EventLogger.getInstance().log("Dandelion spread to (" + newPosition[0] + ", " + newPosition[1] + ")");
    }

    @Override
    protected double getSpreadProbability() {
        return Constants.Plant.Dandelion.SpreadProbability;
    }
}