package organism.plant.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.plant.Plant;
import world.World;

public class Guarana extends Plant {

    public Guarana(int x, int y, World world) {
        super(x, y, Constants.Plant.Guarana.Symbol, Constants.Plant.Guarana.Strength, Constants.Plant.Initiative, world);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = getNewPosition();
        if (newPosition[0] == x && newPosition[1] == y) return;
        world.addOrganism(new Guarana(newPosition[0], newPosition[1], world));
        EventLogger.getInstance().log("Guarana spread to (" + newPosition[0] + ", " + newPosition[1] + ")");
    }

    @Override
    protected double getSpreadProbability() {
        return Constants.Plant.Guarana.SpreadProbability;
    }

    @Override
    public boolean collision(Organism other) {
        other.setStrength(other.getStrength() + 3);
        EventLogger.getInstance().log("Guarana increased the strength of " + other.getClass().getSimpleName() + " by 3 at (" + x + ", " + y + ")");
        die();
        return false;
    }
}