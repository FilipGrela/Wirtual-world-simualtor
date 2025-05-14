package organism.animal;

import organism.Organism;
import world.World;

public abstract class Animal extends Organism {

    public Animal(int x, int y, String symbol, int strength, int initiative, World world) {
        super(x, y, symbol, strength, initiative, world);
    }

    @Override
    public boolean collision(Organism other) {
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

    protected void reproduce() {
        // Implement reproduction logic in subclasses or here if generic
        // Example: spawn a new organism of the same type in a neighboring cell
    }
}