package organism.plant.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.plant.Plant;
import world.World;

public class Belladonna extends Plant {

    public Belladonna(int x, int y, World world) {
        super(x, y, Constants.Plant.Belladonna.Symbol, Constants.Plant.Belladonna.Strength, Constants.Plant.Initiative, world);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = getNewPosition();
        if (newPosition[0] == x && newPosition[1] == y) return;
        world.addOrganism(new Belladonna(newPosition[0], newPosition[1], world));
        EventLogger.getInstance().log("Belladonna spread to (" + newPosition[0] + ", " + newPosition[1] + ")");
    }

    @Override
    protected double getSpreadProbability() {
        return Constants.Plant.Belladonna.SpreadProbability;
    }

    @Override
    public boolean collision(Organism other) {
        EventLogger.getInstance().log("Belladonna has killed " + other.getClass().getSimpleName() + " at (" + x + ", " + y + ")");
        other.die();
        return false;
    }
}