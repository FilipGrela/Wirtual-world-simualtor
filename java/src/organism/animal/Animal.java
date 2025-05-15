package organism.animal;

import logger.EventLogger;
import organism.Organism;
import world.World;

import java.net.URL;

public abstract class Animal extends Organism {

    public Animal(int x, int y, String symbol, int strength, int initiative, World world) {
        super(x, y, symbol, strength, initiative, world);
    }

    @Override
    public boolean collision(Organism other) {
        if (other.getAge() <= 0) {
            return false; // No collision
        }
        if (this.getSymbol() == other.getSymbol()) {
            // Reproduction if same species
            reproduce();
            return false;
        } else {
            // Fight if different species
            return !fight(other);
        }
    }

    protected boolean fight(Organism other) {
        EventLogger.getInstance().log("Fight between " + this.getSymbol() + " and " + other.getSymbol());
        if (this.getStrength() < other.getStrength()) {
            // Log defeat
            // world.getLogger().logEvent("Organism " + this.getSymbol() + " was defeated by " + other.getSymbol());
            this.die();
            return true; // This organism died
        }
        // world.getLogger().logEvent("Organism " + this.getSymbol() + " defeated " + other.getSymbol());
        other.die();
        return false; // This organism survived
    }

    protected abstract void reproduce();
}