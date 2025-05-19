package world;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.OrganismFactory;
import organism.animal.species.*;
import organism.plant.species.*;

import java.util.ArrayList;
import java.util.List;

public abstract class World {
    protected int width;
    protected int height;
    protected  int turns; // liczba tur w grze

    protected int[] humanDirection = new int[]{0, 0};
    protected boolean humanAlive = true;


    // Lista organizmów znajdujących się na świecie
    protected List<Organism> organisms;

    // Konstruktor
    public World(int width, int height) {
        this.width = width;
        this.height = height;
        organisms = new ArrayList<>();
    }

    public List<Organism> getOrganisms() {
        return organisms;
    }

    // Dodaj organizm do świata
    public void addOrganism(Organism org) {
        EventLogger.getInstance().log("Organism " + org.getClass().getSimpleName() + " added at (" + org.getX() + ", " + org.getY() + ")");
        organisms.add(org);
    }

    // Usuwa organizm ze świata
    public void removeOrganism(Organism org) {
        organisms.remove(org);
    }

    // Metoda wykonująca jedną turę gry (wywołuje akcje organizmów i obsługuje kolizje)
    public void executeTurn() {
        EventLogger.getInstance().log("====== Turn " + turns + " ======");
        // sortowanie organizmów po inicjatywie i wieku (starszeństwie)
        organisms.sort((o1, o2) -> {
            if (o2.getInitiative() != o1.getInitiative())
                return o2.getInitiative() - o1.getInitiative();
            else
                return o1.getAge() - o2.getAge();
        });

        // Wykonaj akcje dla każdego organizmu
        for (Organism org : new ArrayList<>(organisms)) {
            org.action();
        }
        turns++;
    }


    // Sprawdza czy współrzędne są na planszy
    public boolean isInside(int x, int y) {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    // Pobiera symbol organizmu na danym polu (do wizualizacji)
    // Jeśli puste pole, zwraca np. '.'
    public String getSymbolAt(int x, int y) {
        for (Organism org : organisms) {
            if (org.getX() == x && org.getY() == y) {
                return org.getSymbol();
            }
        }
        return "."; // puste pole
    }

    // Gettery
    public int getWidth() { return width; }
    public int getHeight() { return height; }

    // Metody pomocnicze do logiki świata, np. znajdowanie organizmu na polu
    public Organism getOrganismAt(int x, int y) {
        for (Organism org : organisms) {
            if (org.getX() == x && org.getY() == y) return org;
        }
        return null;
    }

    public int getTurnCounter() {
        return turns;
    }

    public void setTurnCounter(int turns) {
        this.turns = turns;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public boolean isHumanAlive() {
        for (Organism org : organisms) {
            if (org.getClass().getSimpleName().equals("Human")) return true;
        }
        return false;
    }

    public void clearOrganisms() {
        organisms.clear();
    }

    public void addOrganism(String type, int x, int y) {
        Organism org = OrganismFactory.createOrganism(type, x, y, this);
        if (org != null) {
            addOrganism(org);
        } else {
            EventLogger.getInstance().log("Failed to create organism of type: " + type);
        }
    }

    public void removeOrganismAt(int x, int y) {
        Organism org = getOrganismAt(x, y);
        if (org != null) {
            removeOrganism(org);
        }
    }

    public String[] getAvailableOrganisms(){
        return Constants.Dialog.OrganismToAdd;
    }

    public int[] getHumanDirection() {
        return humanDirection;
    }
    public void setHumanDirection(int[] dir) {
        this.humanDirection = dir;
    }

    public void setHumanAlive(boolean alive) {
        this.humanAlive = alive;
    }
    public abstract int[] findNearestFree(int x, int y);
    public void fillWorld(){
        int count = 5;
        List<int[]> freePositions = new ArrayList<>();
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (getOrganismAt(x, y) == null) {
                    if (x != width/2 || y != height/2) { // nie dodawaj na środku
                        freePositions.add(new int[]{x, y});
                    }
                }
            }
        }
        java.util.Collections.shuffle(freePositions);

        addOrganism(new Human(width/2, height/2, this));

        for (int i = 0; i < count && freePositions.size() >= 3; i++) {
            addOrganism(new Fox(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Wolf(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Sheep(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Turtle(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Antelope(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));

            addOrganism(new Grass(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Dandelion(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Guarana(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new Belladonna(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
            addOrganism(new SosnowskyHogweed(freePositions.removeFirst()[0], freePositions.getFirst()[1], this));
        }

        EventLogger.getInstance().log("World filled with organisms.");
    }// Metoda do wypełnienia świata organizmami na początku gry
    public abstract List<int[]> getNeighbors(int x, int y); // Metoda do pobierania sąsiadów danego pola
}

