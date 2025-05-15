package world;

import java.util.ArrayList;
import java.util.List;

public class WorldSquare extends World {

    public WorldSquare(int width, int height) {
        super(width, height);
    }


    // Dodatkowe metody specyficzne dla planszy kwadratowej (np. pobieranie sąsiadów)
    @Override
    public List<int[]> getNeighbors(int x, int y) {
        List<int[]> neighbors = new ArrayList<>();
        int[][] deltas = { {1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1} }; // 8 directions (including diagonals)

        for (int[] d : deltas) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (isInside(nx, ny)) {
                neighbors.add(new int[]{nx, ny});
            }
        }
        return neighbors;
    }


    // Zwraca najbliższe wolne miejsce w okolicy punktu (lub null, jeśli brak)
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

    @Override
    public int[] getHumanDirection() {
        return humanDirection;
    }

    @Override
    public void setHumanDirection(int[] dir) {
        this.humanDirection = dir;
    }

    @Override
    public void setHumanAlive(boolean alive) {
        this.humanAlive = alive;
    }
}
