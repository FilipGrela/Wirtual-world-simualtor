import ui.MapSelectionWindow;
import ui.GameWindow;
import world.World;

public class Main {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(() -> {
            MapSelectionWindow window = new MapSelectionWindow();
            window.setVisible(true);

            // Czekaj aż użytkownik wybierze mapę i wymiary
            window.setOnMapSelected((mapType, width, height) -> {
                GameWindow gameWindow = new GameWindow(mapType, width, height);
                gameWindow.setVisible(true);
                window.setVisible(false);

                World world = gameWindow.getWorld();
                world.fillWorld();

                // Odśwież widok planszy
                gameWindow.refresh();
            });
        });
    }
}
