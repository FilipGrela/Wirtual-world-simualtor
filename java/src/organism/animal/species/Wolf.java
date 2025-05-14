package organism.animal.species;

import constants.Constants;
import organism.animal.Animal;
import world.World;
import organism.Organism;

public class Wolf extends Animal {

    public Wolf(int x, int y, World world) {
        super(x, y, Constants.Animal.Wolf.Symbol, Constants.Animal.Wolf.Strength, Constants.Animal.Wolf.Initiative, world);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = world.findNearestFree(this.getX(), this.getY());
        if (newPosition != null) {
            // Create a new organism of the same type
            Animal offspring = new Wolf(newPosition[0], newPosition[1], world);
            world.addOrganism(offspring);
        }
    }

    @Override
    public boolean collision(Organism other) {
        return super.collision(other);
    }
}