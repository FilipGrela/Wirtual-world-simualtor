package ui;

import javax.swing.*;
import java.awt.*;
import world.World;
import world.WorldSquare;
import organism.Organism;

public class GameWindow extends JFrame {
    private String mapType;
    private int width, height;
    private JPanel boardPanel;
    private JButton[][] boardButtons;
    private World world;

    public GameWindow(String mapType, int width, int height) {
        this.mapType = mapType;
        this.width = width;
        this.height = height;
        setTitle("Gra: " + (mapType.equals("hex") ? "Hex" : "Szachownica"));
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        setLayout(new BorderLayout());

        // Lewa strona (plansza)
        boardPanel = new JPanel();
        boardPanel.setPreferredSize(new Dimension(400, 600));
        if (mapType.equals("chess")) {
            boardPanel.setLayout(new GridLayout(height, width));
            boardButtons = new JButton[height][width];
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    JButton btn = new JButton();
                    btn.setFocusable(false);
                    btn.setMargin(new Insets(0,0,0,0));
                    btn.setFont(new Font("Segoe UI Emoji", Font.PLAIN, 24));
                    btn.setBackground(Color.WHITE);
                    boardButtons[y][x] = btn;
                    boardPanel.add(btn);
                }
            }
            world = new WorldSquare(width, height);
            drawWorld();
        }
        // hex w przyszłości

        add(boardPanel, BorderLayout.WEST);

        // Prawa strona (logi)
        JPanel logPanel = new JPanel();
        logPanel.setPreferredSize(new Dimension(380, 600));
        logPanel.setLayout(new BorderLayout());

        JTextArea logTextArea = new JTextArea();
        logTextArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logTextArea);
        logPanel.add(scrollPane, BorderLayout.CENTER);

        logTextArea.append("Witaj w grze!\n");

        add(logPanel, BorderLayout.EAST);
    }

    // Aktualizuje widok planszy na podstawie stanu świata
    public void drawWorld() {
        if (!mapType.equals("chess")) return;
        // Najpierw wyczyść planszę
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                boardButtons[y][x].setText("");
            }
        }
        // Ustaw organizmy na planszy
        for (Organism org : world.getOrganisms()) {
            int ox = org.getX();
            int oy = org.getY();
            if (ox >= 0 && ox < width && oy >= 0 && oy < height) {
                boardButtons[oy][ox].setText(String.valueOf(org.getSymbol()));
            }
        }
    }

    public void refresh() {
        drawWorld();
        // Możesz dodać inne odświeżanie widoku w przyszłości
    }

    public World getWorld() {
        return world;
    }
}
