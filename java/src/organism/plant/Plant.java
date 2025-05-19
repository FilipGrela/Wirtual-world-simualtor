package organism.plant;

import organism.Organism;
import world.World;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public abstract class Plant extends Organism {

    public Plant(int x, int y, String symbol, int strength, int initiative, World world) {
        super(x, y, symbol, strength, initiative, world);
    }

    @Override
    public void action() {
        increaseAge();
        if (new Random().nextDouble() > getSpreadProbability()) return;
        reproduce();
    }

    protected int[] getNewPosition() {
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        List<int[]> possible = new ArrayList<>();
        for (int[] d : directions) {
            int nx = x + d[0], ny = y + d[1];
            if (world.isInside(nx, ny) && !isOccupiedBySameType(nx, ny)) {
                possible.add(new int[]{nx, ny});
            }
        }
        if (possible.isEmpty()) return new int[]{x, y};
        return possible.get(new Random().nextInt(possible.size()));
    }

    protected boolean isOccupiedBySameType(int nx, int ny) {
        Organism org = world.getOrganismAt(nx, ny);
        return org != null && org.getSymbol().equals(this.getSymbol());
    }

    @Override
    public boolean collision(Organism other) {
        die();
        return false;
    }

    protected abstract void reproduce();

    protected abstract double getSpreadProbability();
}