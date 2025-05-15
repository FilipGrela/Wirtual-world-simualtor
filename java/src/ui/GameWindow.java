package ui;

import logger.EventLogger;
import logger.EventLoggerListener;
import logger.LogEntry;
import organism.Organism;
import world.World;
import world.WorldSquare;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class GameWindow extends JFrame implements EventLoggerListener {
    private final String mapType;
    private final int width;
    private final int height;
    private final JPanel boardPanel;
    private JButton[][] boardButtons;
    private World world;
    JTextArea logTextArea;

    public GameWindow(String mapType, int width, int height) {
        this.mapType = mapType;
        this.width = width;
        this.height = height;
        setTitle("Gra: " + (mapType.equals("hex") ? "Hex" : "Szachownica"));
        setSize(600, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        setLayout(new BorderLayout());

        // Górna część (plansza)
        boardPanel = new JPanel() {
            @Override
            public Dimension getPreferredSize() {
                // Oblicz kwadratowe przyciski
                int buttonSize = Math.min(getWidth() / width, getHeight() / height);
                return new Dimension(buttonSize * width, buttonSize * height);
            }

            @Override
            public void doLayout() {
                super.doLayout();
                int buttonSize = Math.min(getWidth() / width, getHeight() / height);
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        JButton btn = boardButtons[y][x];
                        btn.setBounds(x * buttonSize, y * buttonSize, buttonSize, buttonSize);
                    }
                }
            }
        };
        boardPanel.setLayout(null); // Ustaw layout na null, aby ręcznie zarządzać rozmiarem i pozycją przycisków
        boardButtons = new JButton[height][width];
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                ImageIcon foxIcon = new ImageIcon(); // ścieżka względna w JAR lub folderze resources

                JButton btn = new JButton();
                btn.setContentAreaFilled(false);
                btn.setContentAreaFilled(true);
                btn.setBorderPainted(true);
                btn.setBackground(new Color(250, 250, 250));
                btn.setOpaque(true);

                boardButtons[y][x] = btn;
                boardPanel.add(btn);
            }
        }
        boardPanel.setBackground(new Color(235, 235, 235));
        world = new WorldSquare(width, height);
        drawWorld();

        add(boardPanel, BorderLayout.CENTER);

        // Dolna część (logi)
        JPanel logPanel = new JPanel();
        logPanel.setPreferredSize(new Dimension(800, 200)); // 1/3 wysokości okna
        logPanel.setLayout(new BorderLayout());
        logPanel.setBackground(Color.WHITE);

        logTextArea = new JTextArea();
        logTextArea.setEditable(false);
        logTextArea.setFont(new Font("Segoe UI Emoji", Font.PLAIN, 16));
        logTextArea.setBackground(new Color(245, 245, 245));
        logTextArea.setForeground(new Color(40, 40, 40));
        logTextArea.setBorder(BorderFactory.createEmptyBorder(16, 16, 16, 16));
        logTextArea.setLineWrap(true);
        logTextArea.setWrapStyleWord(true);

        JScrollPane scrollPane = new JScrollPane(logTextArea);
        scrollPane.setBorder(BorderFactory.createEmptyBorder());
        scrollPane.setBackground(Color.WHITE);
        scrollPane.getVerticalScrollBar().setUnitIncrement(16);

        logPanel.add(scrollPane, BorderLayout.CENTER);

        add(logPanel, BorderLayout.SOUTH);

        EventLogger.getInstance().addListener(this);
    }

    // Update log area when logs change
    @Override
    public void onLogChanged(List<LogEntry> logs) {
        StringBuilder sb = new StringBuilder(logTextArea.getText());
        for (LogEntry entry : logs) {
            sb.append(entry.toString()).append("\n");
        }
        logTextArea.setText(sb.toString());
        logTextArea.setCaretPosition(logTextArea.getDocument().getLength());
        EventLogger.getInstance().clear();
    }

    // Aktualizuje widok planszy na podstawie stanu świata
    public void drawWorld() {
        // Clear all buttons
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                boardButtons[y][x].setIcon(null);
                boardButtons[y][x].setText("");
            }
        }
        // Set icons for organisms
        for (Organism org : world.getOrganisms()) {
            int ox = org.getX();
            int oy = org.getY();
            if (ox >= 0 && ox < width && oy >= 0 && oy < height) {
                String imagePath = org.getSymbol(); // e.g. "/images/fox.png"
                java.net.URL imgUrl = getClass().getResource(imagePath);
                if (imgUrl != null) {
                    ImageIcon icon = new ImageIcon(imgUrl);
                    int buttonSize = Math.min(boardButtons[oy][ox].getWidth(), boardButtons[oy][ox].getHeight());
                    Image scaledImg = icon.getImage().getScaledInstance(buttonSize, buttonSize, Image.SCALE_SMOOTH);
                    boardButtons[oy][ox].setIcon(new ImageIcon(scaledImg));
                }
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
