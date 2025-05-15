package organism.animal.species;

import constants.Constants;
import organism.Organism;
import organism.animal.Animal;
import world.World;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Fox extends Animal {

    public Fox(int x, int y, World world) {
        super(x, y, Constants.Animal.Fox.Symbol, Constants.Animal.Fox.Strength, Constants.Animal.Fox.Initiative, world); // Symbol, strength, and initiative for Fox
    }

    @Override
    protected void reproduce() {
        int[] newPosition = world.findNearestFree(x, y);
        if (newPosition == null) {
            return; // No free space for reproduction
        }
        world.addOrganism(new Fox(newPosition[0], newPosition[1], world));
    }

    @Override
    protected int[] getNewPosition() {
        List<int[]> directions = new ArrayList<>();
        directions.add(new int[]{0, 1});    // Up
        directions.add(new int[]{1, 0});    // Right
        directions.add(new int[]{0, -1});   // Down
        directions.add(new int[]{-1, 0});   // Left
        directions.add(new int[]{1, 1});    // Up-Right
        directions.add(new int[]{1, -1});   // Down-Right
        directions.add(new int[]{-1, 1});   // Up-Left
        directions.add(new int[]{-1, -1});  // Down-Left

        Random rand = new Random();
        while (!directions.isEmpty()) {
            int idx = rand.nextInt(directions.size());
            int[] dir = directions.remove(idx);
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (world.isInside(nx, ny) && !isStrongerOrganismPresent(nx, ny)) {
                return new int[]{nx, ny};
            }
        }
        return new int[]{x, y}; // Stay in place if no valid move is found
    }

    private boolean isStrongerOrganismPresent(int nx, int ny) {
        Organism organism = world.getOrganismAt(nx, ny);
        return organism != null && organism.getStrength() > this.getStrength();
    }
}
