package ui;

import organism.Organism;
import world.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class GameBoardSquare extends JPanel implements GameBoard {
    private final int width;
    private final int height;
    private final JButton[][] boardButtons;
    private final World world;

    private final Map<String, ImageIcon> imageCache = new HashMap<>();

    public GameBoardSquare(int width, int height, World world) {
        this.width = width;
        this.height = height;
        this.world = world;

        setLayout(null); // Manual layout for square buttons
        boardButtons = new JButton[height][width];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                JButton btn = new JButton();
                btn.setFocusable(false);
                btn.setMargin(new Insets(0, 0, 0, 0));
                btn.setFont(new Font("Segoe UI Emoji", Font.PLAIN, 12));
                btn.setBackground(new Color(250, 250, 250));
                btn.setForeground(new Color(40, 40, 40));
                btn.setBorder(BorderFactory.createCompoundBorder(
                        BorderFactory.createLineBorder(new Color(220, 220, 220), 2, true),
                        BorderFactory.createEmptyBorder(8, 8, 8, 8)
                ));
                btn.setOpaque(true);
                btn.setFocusPainted(false);

                boardButtons[y][x] = btn;
                add(btn);
            }
        }
    }

    private void showOrganismSelection(int x, int y, int buttonSize) {
        OrganismAddDialog.showOrganismSelection(
                this,
                world.getAvailableOrganisms(),
                x * buttonSize, y * buttonSize,
                e -> {
                    String organism = ((JMenuItem) e.getSource()).getText();
                    world.removeOrganismAt(x, y);
                    world.addOrganism(organism, x, y);
                    drawWorld();
                }
        );
    }

    private ImageIcon getCachedIcon(String path, int size) {
        String key = path + "#" + size;
        return imageCache.computeIfAbsent(key, k -> {
            java.net.URL url = getClass().getResource(path);
            if (url != null) {
                ImageIcon icon = new ImageIcon(url);
                Image scaledImg = icon.getImage().getScaledInstance(size, size, Image.SCALE_SMOOTH);
                return new ImageIcon(scaledImg);
            }
            return null;
        });
    }

    @Override
    public Dimension getPreferredSize() {
        int buttonSize = Math.min(getWidth() / width, getHeight() / height);
        return new Dimension(buttonSize * width, buttonSize * height);
    }

    @Override
    public void doLayout() {
        int buttonSize = Math.min(getWidth() / width, getHeight() / height);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                JButton btn = boardButtons[y][x];

                btn.setBounds(x* buttonSize, y * buttonSize, buttonSize, buttonSize);
                // Remove all previous action listeners to avoid stacking
                for (ActionListener al : btn.getActionListeners()) {
                    btn.removeActionListener(al);
                }

                final int dimX = x;
                final int dimY = y;
                btn.addActionListener(e -> showOrganismSelection(dimX, dimY, buttonSize));
            }
        }
    }

    @Override
    public void drawWorld() {
        // Clear all buttons
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                boardButtons[y][x].setIcon(null);
                boardButtons[y][x].setText("");
            }
        }
        // Set icons for organisms using cache
        for (Organism org : world.getOrganisms()) {
            int ox = org.getX();
            int oy = org.getY();
            if (ox >= 0 && ox < width && oy >= 0 && oy < height) {
                String imagePath = org.getSymbol();
                int buttonSize = Math.min(boardButtons[oy][ox].getWidth(), boardButtons[oy][ox].getHeight());
                ImageIcon cachedIcon = getCachedIcon(imagePath, buttonSize);
                if (cachedIcon != null) {
                    boardButtons[oy][ox].setIcon(cachedIcon);
                }
            }
        }
    }
}
