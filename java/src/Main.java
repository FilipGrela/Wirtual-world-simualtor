import logger.EventLogger;
import ui.GameWindow;
import ui.MapSelectionWindow;
import world.World;

import java.awt.event.KeyEvent;

public class Main {
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(Main::createAndShowMapSelectionWindow);
    }

    private static void createAndShowMapSelectionWindow() {
        MapSelectionWindow window = new MapSelectionWindow();
        window.setVisible(true);

        window.setOnMapSelected((mapType, width, height) -> {
            startGame(window, mapType, width, height);
        });
    }

    private static void startGame(MapSelectionWindow window, String mapType, int width, int height) {
        GameWindow gameWindow = new GameWindow(mapType, width, height);
        gameWindow.setVisible(true);
        gameWindow.requestFocusInWindow();
        window.setVisible(false);

        World world = gameWindow.getWorld();
        world.fillWorld();

        gameWindow.refresh();

        // Add a key listener to the game window to handle key events
        gameWindow.addKeyListener(new java.awt.event.KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                EventLogger.getInstance().log(String.valueOf(e.getKeyCode()));
                if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    gameWindow.dispose();
                    createAndShowMapSelectionWindow();
                } else if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                    world.executeTurn();
                    gameWindow.refresh();
                }
            }
        });
    }
}