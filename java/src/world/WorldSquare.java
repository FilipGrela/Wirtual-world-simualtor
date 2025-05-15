package world;

import logger.EventLogger;
import organism.Organism;
import organism.animal.species.Fox;
import organism.animal.species.Sheep;
import organism.animal.species.Wolf;

import java.util.ArrayList;
import java.util.List;

public class WorldSquare extends World {

    public WorldSquare(int width, int height) {
        super(width, height);
    }

    @Override
    public void executeTurn() {
        EventLogger.getInstance().log("====== Turn " + turns + " ======");
        // Przykładowa implementacja kolejności wykonywania ruchów i akcji organizmów
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

        // Tutaj można obsłużyć kolizje, rozprzestrzenianie się, itp.
        turns++;
    }

    @Override
    public void drawWorld() {
        // Rysowanie obsługuje GameWindow (GUI) - metoda pusta
    }

    // drawWorld obsługuje teraz GameWindow

    // Dodatkowe metody specyficzne dla planszy kwadratowej (np. pobieranie sąsiadów)
    public List<int[]> getNeighbors(int x, int y) {
        List<int[]> neighbors = new ArrayList<>();
        int[][] deltas = { {1,0}, {-1,0}, {0,1}, {0,-1} }; // 4 kierunki

        for (int[] d : deltas) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (isInside(nx, ny)) {
                neighbors.add(new int[]{nx, ny});
            }
        }
        return neighbors;
    }

    // Metoda do dodawania organizmów do świata
    @Override
    public void fillWorld(){
        int count = 3;
        List<int[]> freePositions = new ArrayList<>();
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                if (getOrganismAt(x, y) == null) {
                    freePositions.add(new int[]{x, y});
                }
            }
        }
        java.util.Collections.shuffle(freePositions);

        for (int i = 0; i < count && freePositions.size() >= 3; i++) {
            addOrganism(new Fox(freePositions.remove(0)[0], freePositions.get(0)[1], this));
            addOrganism(new Wolf(freePositions.remove(0)[0], freePositions.get(0)[1], this));
            addOrganism(new Sheep(freePositions.remove(0)[0], freePositions.get(0)[1], this));
        }
    }

    // Zwraca najbliższe wolne miejsce w okolicy punktu (lub null jeśli brak)
    public int[] findNearestFree(int x, int y) {
        int[][] directions = {
            {0, 1},    // Up
            {1, 0},    // Right
            {0, -1},   // Down
            {-1, 0},   // Left
            {1, 1},    // Up-Right
            {1, -1},   // Down-Right
            {-1, 1},   // Up-Left
            {-1, -1}   // Down-Left
        };
        for (int[] dir : directions) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (isInside(nx, ny) && getOrganismAt(nx, ny) == null) {
                return new int[]{nx, ny};
            }
        }
        return null;
    }
}
