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
        // Find a free neighboring cell

    }

    @Override
    public boolean collision(Organism other) {
        return super.collision(other);
    }
}