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
        setTitle("Gra: " + (mapType.equals("hex") ? "Hex" : "Szachownica") + " Filip Grela 203850" );
        setSize(600, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        setLayout(new BorderLayout());

        // Add this at the start of your GameWindow constructor, after setTitle(...)
        JMenuBar menuBar = new JMenuBar();
        JMenu gameMenu = new JMenu("Game");
        JMenuItem loadItem = new JMenuItem("Load Game");
        JMenuItem saveItem = new JMenuItem("Save Game");

        gameMenu.add(loadItem);
        gameMenu.add(saveItem);
        menuBar.add(gameMenu);
        setJMenuBar(menuBar);

        // Example: add action listeners for future implementation
        loadItem.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser(".");
            fileChooser.setDialogTitle("Select save file");
            fileChooser.setFileFilter(new javax.swing.filechooser.FileNameExtensionFilter("JSON files", "json"));
            int result = fileChooser.showOpenDialog(this);
            if (result == JFileChooser.APPROVE_OPTION) {
                String filename = fileChooser.getSelectedFile().getAbsolutePath();
                saveManager.SaveManager.loadWorldFromFile(world, filename);
                refresh();
                JOptionPane.showMessageDialog(this, "Game loaded from " + filename);
            }
        });
        saveItem.addActionListener(e -> {
            String filename = JOptionPane.showInputDialog(this, "Enter save file name:", "Save Game", JOptionPane.PLAIN_MESSAGE);
            if (filename != null && !filename.trim().isEmpty()) {
                if (!filename.endsWith(".json")) filename += ".json";
                saveManager.SaveManager.saveWorldToFile(world, filename);
                JOptionPane.showMessageDialog(this, "Game saved as " + filename);
            }
        });
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

        // Panel wyszukiwania
        JPanel searchPanel = new JPanel(new BorderLayout());
        JLabel searchLabel = new JLabel("Szukaj w logach: ");
        JTextField searchField = new JTextField();
        searchPanel.add(searchLabel, BorderLayout.WEST);
        searchPanel.add(searchField, BorderLayout.CENTER);

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

        logPanel.add(searchPanel, BorderLayout.NORTH);
        logPanel.add(scrollPane, BorderLayout.CENTER);

        add(logPanel, BorderLayout.SOUTH);

        // Listener do wyszukiwania w logach
        searchField.getDocument().addDocumentListener(new javax.swing.event.DocumentListener() {
            private void filterLogs() {
                String query = searchField.getText().toLowerCase();
                String[] lines = logTextArea.getText().split("\n");
                StringBuilder filtered = new StringBuilder();
                for (String line : lines) {
                    if (line.toLowerCase().contains(query)) {
                        filtered.append(line).append("\n");
                    }
                }
                logTextArea.setText(filtered.toString());
            }
            public void insertUpdate(javax.swing.event.DocumentEvent e) { filterLogs(); }
            public void removeUpdate(javax.swing.event.DocumentEvent e) { filterLogs(); }
            public void changedUpdate(javax.swing.event.DocumentEvent e) { filterLogs(); }
        });

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
                    Icon currentIcon = boardButtons[oy][ox].getIcon();
                    Image currentImg = currentIcon instanceof ImageIcon ? ((ImageIcon) currentIcon).getImage() : null;
                    if (currentImg == null || !currentImg.equals(scaledImg)) {
                        boardButtons[oy][ox].setIcon(new ImageIcon(scaledImg));
                    }
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
