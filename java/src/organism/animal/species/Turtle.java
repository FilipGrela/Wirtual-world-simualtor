package organism.animal.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.animal.Animal;
import world.World;

import java.util.Random;

public class Turtle extends Animal {

    public Turtle(int x, int y, World world) {
        super(x, y, Constants.Animal.Turtle.Symbol, Constants.Animal.Turtle.Strength, Constants.Animal.Turtle.Initiative, world);
    }

    @Override
    protected int[] getNewPosition() {
        Random rand = new Random();
        // 75% chance to stay in place
        if (rand.nextInt(4) != 0) {
            return new int[]{x, y};
        }
        // Otherwise, move like a normal animal (random neighbor)
        int[][] directions = {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0},
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };
        int[] dir = directions[rand.nextInt(directions.length)];
        int nx = x + dir[0];
        int ny = y + dir[1];
        if (world.isInside(nx, ny)) {
            return new int[]{nx, ny};
        }
        return new int[]{x, y};
    }

    @Override
    public boolean collision(Organism other) {
        // Deflect attack if attacker is animal and has strength < 5
        if (other instanceof Animal && other.getStrength() < 5) {
            EventLogger.getInstance().log("Turtle deflected attack from " + other.getClass().getSimpleName() + " at (" + x + ", " + y + ")");
            // Attacker should stay in its previous position (handled in world logic)
            return false;
        }
        return super.collision(other);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = world.findNearestFree(this.getX(), this.getY());
        if (newPosition != null) {
            Animal offspring = new Turtle(newPosition[0], newPosition[1], world);
            world.addOrganism(offspring);
            EventLogger.getInstance().log("Turtle reproduced at (" + newPosition[0] + ", " + newPosition[1] + ")");
        }
    }
}