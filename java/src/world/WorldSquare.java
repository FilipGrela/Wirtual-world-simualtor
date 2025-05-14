package world;

import organism.Organism;
import organism.animal.species.Wolf;

import java.util.ArrayList;
import java.util.List;

public class WorldSquare extends World {

    public WorldSquare(int width, int height) {
        super(width, height);
    }

    @Override
    public void executeTurn() {
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
        // Przykładowe dodanie organizmów do świata
        // Można to zrobić w inny sposób, np. z pliku konfiguracyjnego
        for (int i = 0; i < 5; i++) {
             addOrganism(new Wolf(i, i, this));
        }
    }
}
