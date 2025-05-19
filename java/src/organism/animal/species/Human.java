package organism.animal.species;

import constants.Constants;
import logger.EventLogger;
import organism.animal.Animal;
import world.World;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Human extends Animal {
    private boolean abilityActive = false;
    private int abilityCooldown = 0;
    private int abilityDuration = 0;

    public Human(int x, int y, World world) {
        super(x, y, Constants.Animal.Human.Symbol, Constants.Animal.Human.Strength, Constants.Animal.Human.Initiative, world);
    }

    @Override
    protected void reproduce() {
        int[] newPosition = world.findNearestFree(x, y);
        if (newPosition == null) return;
        world.addOrganism(new Human(newPosition[0], newPosition[1], world));
    }

    @Override
    protected int[] getNewPosition() {
        int[] dir = world.getHumanDirection();
        int nx = x + dir[0];
        int ny = y + dir[1];
        if (world.isInside(nx, ny)) {
            return new int[]{nx, ny};
        }
        return new int[]{x, y};
    }

    public boolean isHuman() {
        return true;
    }

    @Override
    public void die() {
        if (abilityActive) {
            escapeToRandomPosition();
            EventLogger.getInstance().log("Human avoided death using special ability!");
            return;
        }
        world.setHumanAlive(false);
        super.die();
    }

    public void activateAbility() {
        if (abilityCooldown == 0 && !abilityActive) {
            changeSymbol(Constants.Animal.Human.SymbolActiveAbility);
            abilityActive = true;
            abilityDuration = Constants.Animal.Human.AbilityDuration;
            EventLogger.getInstance().log("Special ability activated!");
        } else if (abilityCooldown > 0) {
            EventLogger.getInstance().log("Ability is on cooldown for " + abilityCooldown + " turns.");
        } else {
            EventLogger.getInstance().log("Ability is already active!");
        }
    }

    @Override
    public void action() {
        if (abilityActive) {
            abilityDuration--;
            if (abilityDuration < 0) {
                changeSymbol(Constants.Animal.Human.Symbol);
                abilityActive = false;
                abilityCooldown = Constants.Animal.Human.AbilityCooldown;
                EventLogger.getInstance().log("Special ability deactivated!");
            }
        } else if (abilityCooldown > 0) {
            abilityCooldown--;
        }
        super.action();
    }

    private void escapeToRandomPosition() {
        int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        List<int[]> possiblePositions = new ArrayList<>();
        for (int[] d : directions) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (world.isInside(nx, ny) && world.getOrganismAt(nx, ny) == null) {
                possiblePositions.add(new int[]{nx, ny});
            }
        }
        if (!possiblePositions.isEmpty()) {
            Random rand = new Random();
            int[] newPosition = possiblePositions.get(rand.nextInt(possiblePositions.size()));
            setPosition(newPosition[0], newPosition[1]);
            EventLogger.getInstance().log("Human escaped death and moved to a new field!");
        } else {
            EventLogger.getInstance().log("Human has nowhere to escape, stays in place!");
        }
    }

    public int getAbilityCooldown() {
        return abilityCooldown;
    }

    // Getters and setters for ability state
    public void setAbilityCooldown(int cooldown) {
        this.abilityCooldown = cooldown;
    }

    public int getAbilityDuration() {
        return abilityDuration;
    }

    public void setAbilityDuration(int duration) {
        this.abilityDuration = duration;
    }

    public boolean isAbilityActive() {
        return abilityActive;
    }

    public void setAbilityActive(boolean active) {
        this.abilityActive = active;
    }
}