package world;

import constants.Constants;
import logger.EventLogger;
import organism.Organism;
import organism.OrganismFactory;

import java.util.ArrayList;
import java.util.List;

public abstract class World {
    protected int width;
    protected int height;

    protected int type;
    protected  int turns; // liczba tur w grze


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
    public abstract void executeTurn();


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

    public abstract int[] getHumanDirection();
    public abstract void setHumanDirection(int[] dir);
    public abstract void setHumanAlive(boolean alive);

    public abstract int[] findNearestFree(int x, int y);
    public abstract void fillWorld(); // Metoda do wypełnienia świata organizmami na początku gry
    public abstract List<int[]> getNeighbors(int x, int y); // Metoda do pobierania sąsiadów danego pola
}

