package world;

import java.util.ArrayList;
import java.util.List;

public class WorldHex extends World {

    public WorldHex(int width, int height) {
        super(width, height);
    }

    // Dodatkowe metody specyficzne dla planszy heksagonalnej (pobieranie sąsiadów)
    @Override
    public List<int[]> getNeighbors(int x, int y) {
        List<int[]> neighbors = new ArrayList<>();
        // W układzie heksagonalnym offset zależy od parzystości wiersza (even-q vertical layout)
        int[][] evenDeltas = {{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}};
        int[][] oddDeltas = {{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}};
        int[][] deltas = (y % 2 == 0) ? evenDeltas : oddDeltas;

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
        // Kierunki sąsiadów w układzie heksagonalnym (even-q vertical layout)
        int[][] evenDeltas = {{+1, 0}, {0, -1}, {-1, -1}, {-1, 0}, {-1, +1}, {0, +1}};
        int[][] oddDeltas = {{+1, 0}, {+1, -1}, {0, -1}, {-1, 0}, {0, +1}, {+1, +1}};
        int[][] deltas = (y % 2 == 0) ? evenDeltas : oddDeltas;

        for (int[] d : deltas) {
            int nx = x + d[0];
            int ny = y + d[1];
            if (isInside(nx, ny) && getOrganismAt(nx, ny) == null) {
                return new int[]{nx, ny};
            }
        }
        return null;
    }
}
