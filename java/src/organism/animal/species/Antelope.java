package organism.animal.species;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.animal.Animal;
import world.World;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Antelope extends Animal {
    public Antelope(int x, int y, World world) {
        super(x, y, Constants.Animal.Antelope.Symbol, Constants.Animal.Antelope.Strength, Constants.Animal.Antelope.Initiative, world);
    }

    @Override
    protected int[] getNewPosition() {
        // Antelope moves 2 fields in one direction
        int[][] directions = {
            {0, 2}, {2, 0}, {0, -2}, {-2, 0},
            {0, 1}, {1, 0}, {0, -1}, {-1, 0},
            {2, 2}, {2, -2}, {-2, 2}, {-2, -2}, // diagonal moves (2 fields)
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}  // diagonal moves (1 field)
        };
        List<int[]> possibleMoves = new ArrayList<>();
        for (int[] dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (world.isInside(nx, ny)) {
                possibleMoves.add(new int[]{nx, ny});
            }
        }
        if (possibleMoves.isEmpty()) return new int[]{x, y};
        return possibleMoves.get(new Random().nextInt(possibleMoves.size()));
    }

    @Override
    public boolean collision(Organism other) {
        // 50% chance to escape
        if (new Random().nextBoolean()) {
            int[] escapePos = getNewPosition();
            if (escapePos[0] != x || escapePos[1] != y) {
                this.move(escapePos[0], escapePos[1]);
                EventLogger.getInstance().log("Antelope escaped from " + other.getClass().getName() + " at (" + x + ", " + y + ")");
                return false;
            }
        }
        return super.collision(other);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = world.findNearestFree(this.getX(), this.getY());
        if (newPosition != null) {
            Animal offspring = new Antelope(newPosition[0], newPosition[1], world);
            world.addOrganism(offspring);
            EventLogger.getInstance().log("Antelope reproduced at (" + newPosition[0] + ", " + newPosition[1] + ")");
        }
    }
}