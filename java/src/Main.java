import logger.EventLogger;
import organism.animal.species.Human;
import ui.GameWindow;
import ui.MapSelectionWindow;
import world.World;

import java.awt.event.KeyEvent;
import java.util.HashMap;
import java.util.Map;

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

//        startGame(window, "chess", 8, 8);
    }

    private static void startGame(MapSelectionWindow window, String mapType, int width, int height) {
        GameWindow gameWindow = new GameWindow(mapType, width, height);
        gameWindow.setVisible(true);
        gameWindow.setFocusableWindowState(true);
        gameWindow.requestFocus();
        window.setVisible(false);

        World world = gameWindow.getWorld();
        world.fillWorld();

        gameWindow.refresh();

        // Add a key listener to the game window to handle key events
        Map<Integer, int[]> directionMap = new HashMap<>();
        directionMap.put(KeyEvent.VK_UP, new int[]{0, -1});
        directionMap.put(KeyEvent.VK_DOWN, new int[]{0, 1});
        directionMap.put(KeyEvent.VK_LEFT, new int[]{-1, 0});
        directionMap.put(KeyEvent.VK_RIGHT, new int[]{1, 0});
        directionMap.put(KeyEvent.VK_NUMPAD1, new int[]{-1, 1});
        directionMap.put(KeyEvent.VK_NUMPAD2, new int[]{0, 1});
        directionMap.put(KeyEvent.VK_NUMPAD3, new int[]{1, 1});
        directionMap.put(KeyEvent.VK_NUMPAD4, new int[]{-1, 0});
        directionMap.put(KeyEvent.VK_NUMPAD6, new int[]{1, 0});
        directionMap.put(KeyEvent.VK_NUMPAD7, new int[]{-1, -1});
        directionMap.put(KeyEvent.VK_NUMPAD8, new int[]{0, -1});
        directionMap.put(KeyEvent.VK_NUMPAD9, new int[]{1, -1});

        gameWindow.addKeyListener(new java.awt.event.KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                EventLogger.getInstance().log(String.valueOf(e.getKeyCode()));
                if (e.getKeyCode() == KeyEvent.VK_ESCAPE) {
                    gameWindow.dispose();
                    createAndShowMapSelectionWindow();
                } else if (e.getKeyCode() == KeyEvent.VK_SPACE) {
                    world.setHumanDirection(new int[]{0, 0});
                    world.executeTurn();
                    gameWindow.refresh();
                } else if (directionMap.containsKey(e.getKeyCode())) {
                    world.setHumanDirection(directionMap.get(e.getKeyCode()));
                    world.executeTurn();
                    gameWindow.refresh();
                } else if (e.getKeyCode() == KeyEvent.VK_A) { // Example: activate ability with 'A'
                    // Find human and activate ability
                    for (var org : world.getOrganisms()) {
                        if (org instanceof Human) {
                            ((Human) org).activateAbility();
                        }
                    }
                }
            }
        });
    }
}