package world;

import organism.Organism;

import java.util.List;
import java.util.ArrayList;

public abstract class World {
    protected int width;
    protected int height;

    // Typ świata (np. kwadratowy, prostokątny, itp.)
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
        organisms.add(org);
    }

    // Usuwa organizm ze świata
    public void removeOrganism(Organism org) {
        organisms.remove(org);
    }

    // Metoda wykonująca jedną turę gry (wywołuje akcje organizmów i obsługuje kolizje)
    public abstract void executeTurn();

    // Metoda rysująca świat (np. do konsoli lub GUI)
    public abstract void drawWorld();

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

    public abstract void fillWorld(); // Metoda do wypełnienia świata organizmami na początku gry
}

