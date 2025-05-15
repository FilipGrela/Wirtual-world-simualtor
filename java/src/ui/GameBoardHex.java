package ui;

import organism.Organism;
import world.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

public class GameBoardHex extends JPanel implements GameBoard {
    private final int width;
    private final int height;
    private final JButton[][] boardButtons;
    private final World world;

    private final Map<String, ImageIcon> imageCache = new HashMap<>();

    public GameBoardHex(int width, int height, World world) {
        this.width = width;
        this.height = height;
        this.world = world;

        setLayout(null); // Manual layout for hexagonal buttons
        boardButtons = new JButton[height][width];

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                HexButton btn = new HexButton();
                btn.setPreferredSize(getPreferredSize());
                btn.setFocusable(false);
                btn.setMargin(new Insets(0, 0, 0, 0));
                btn.setFont(new Font("Segoe UI Emoji", Font.PLAIN, 12));
                btn.setBackground(new Color(250, 250, 250));
                btn.setForeground(new Color(40, 40, 40));
                btn.setBorder(BorderFactory.createLineBorder(new Color(220, 220, 220), 2));
                btn.setOpaque(false);
                btn.setFocusPainted(false);

                boardButtons[y][x] = btn;
                add(btn);
            }
        }
    }

    private void showOrganismSelection(int x, int y, final int buttonSize) {
        OrganismAddDialog.showOrganismSelection(
                this,
                world.getAvailableOrganisms(),
                (int) (x * buttonSize * 0.6 + 0.5), (int) (y * buttonSize * 0.5 + 0.5),
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
        double hexRatio = Math.sqrt(3) / 2;
        int panelW = getWidth() > 0 ? getWidth() : 1;
        int panelH = getHeight() > 0 ? getHeight() : 1;
        int buttonSizeW = (int) (panelW / (width));
        int buttonSizeH = (int) (panelH / (height));
        int buttonSize = Math.min(buttonSizeW, buttonSizeH);

        int hexWidth = buttonSize;
        int hexHeight = (int) (buttonSize * hexRatio * 2);
        int totalWidth = (int) (width * hexWidth + hexWidth / 2.0);
//        int totalHeight = (int) ((height - 1) * (hexHeight * 0.5) + hexHeight);
        int totalHeight = (int) (height * hexHeight + hexHeight / 2.0);
        return new Dimension(totalWidth, totalHeight);
    }

    @Override
    public void doLayout() {
        double hexRatio = Math.sqrt(3) / 2;
        int panelW = getWidth() > 0 ? getWidth() : 1;
        int panelH = getHeight() > 0 ? getHeight() : 1;
        int buttonSizeW = (int) (panelW / (width*0.6 + 0.5));
        int buttonSizeH = (int) (panelH / (height * 0.5 + 0.5));
        int buttonSize = Math.min(buttonSizeW, buttonSizeH);

        int hexWidth = (int) (buttonSize * 0.6);
        int hexHeight = (int) (buttonSize * hexRatio * 1.2);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                JButton btn = boardButtons[y][x];
                int offsetX = (y % 2 == 0) ? 0 : hexWidth / 2;
                int dimX = x * hexWidth + offsetX;
                int dimY = (int) (y * (hexHeight * 0.5));

                btn.setBounds(dimX, dimY, hexWidth, hexHeight);

                for (ActionListener al : btn.getActionListeners()) {
                    btn.removeActionListener(al);
                }
                int finalX = x, finalY = y;
                int finalButtonSize = buttonSize;
                btn.addActionListener(e -> showOrganismSelection(finalX, finalY, finalButtonSize));
            }
        }
    }

    @Override
    public void drawWorld() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                boardButtons[y][x].setIcon(null);
                boardButtons[y][x].setText("");
            }
        }
        for (Organism org : world.getOrganisms()) {
            int ox = org.getX();
            int oy = org.getY();
            if (ox >= 0 && ox < width && oy >= 0 && oy < height) {
                String imagePath = org.getSymbol();
                int buttonSize = Math.min(boardButtons[oy][ox].getWidth(), boardButtons[oy][ox].getHeight());
                double scaleFactor = 0.6;
                int scaledSize = (int) (buttonSize * scaleFactor);
                ImageIcon cachedIcon = getCachedIcon(imagePath, scaledSize);
                if (cachedIcon != null) {
                    boardButtons[oy][ox].setIcon(cachedIcon);
                }
            }
        }
    }
}
