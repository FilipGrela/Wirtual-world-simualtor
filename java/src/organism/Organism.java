package organism;

import world.World;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public abstract class Organism {
    protected int x, y;
    protected String symbol;
    protected int strength;
    protected int initiative;
    protected int age;
    protected int previousX, previousY;
    protected World world;

    public Organism(int x, int y, String symbol, int strength, int initiative, World world) {
        this.x = x;
        this.y = y;
        this.symbol = symbol;
        this.strength = strength;
        this.initiative = initiative;
        this.age = 0;
        this.world = world;
        this.previousX = x;
        this.previousY = y;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setPosition(int x, int y) {
        this.previousX = this.x;
        this.previousY = this.y;
        this.x = x;
        this.y = y;
    }

    public int getStrength() {
        return strength;
    }

    public void setStrength(int strength) {
        this.strength = strength;
    }

    public int getInitiative() {
        return initiative;
    }

    public void setInitiative(int initiative) {
        this.initiative = initiative;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int increaseAge() {
        return ++age;
    }

    public String getSymbol() {
        return symbol;
    }

    public void changeSymbol(String newSymbol) {
        this.symbol = newSymbol;
    }

    public int getPreviousX() {
        return previousX;
    }

    public int getPreviousY() {
        return previousY;
    }

    // Returns a random valid neighbor position (4 or 8 directions)
    protected int[] getNewPosition() {
        List<int[]> directions = new ArrayList<>();
        directions.add(new int[]{0, 1});
        directions.add(new int[]{1, 0});
        directions.add(new int[]{0, -1});
        directions.add(new int[]{-1, 0});
        directions.add(new int[]{1, 1});
        directions.add(new int[]{1, -1});
        directions.add(new int[]{-1, 1});
        directions.add(new int[]{-1, -1});

        Random rand = new Random();
        while (!directions.isEmpty()) {
            int idx = rand.nextInt(directions.size());
            int[] dir = directions.remove(idx);
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (world.isInside(nx, ny)) {
                return new int[]{nx, ny};
            }
        }
        return new int[]{x, y};
    }

    public void action() {
        increaseAge();
        int[] newPos = getNewPosition();
        move(newPos[0], newPos[1]);
    }

    public void move(int newX, int newY) {
        Organism other = world.getOrganismAt(newX, newY);
        boolean isThisOrganismDeleted = false;
        if (other != null && other != this) {
            isThisOrganismDeleted = other.collision(this);
        }
        if (!isThisOrganismDeleted && world.getOrganismAt(newX, newY) == null) {
            setPosition(newX, newY);
        }
    }

    public void die() {
        world.removeOrganism(this);
    }

    // Abstract: must be implemented in subclasses
    public abstract boolean collision(Organism attacker);
}
