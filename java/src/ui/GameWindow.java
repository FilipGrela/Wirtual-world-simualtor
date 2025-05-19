package ui;

import logger.EventLogger;
import logger.EventLoggerListener;
import logger.LogEntry;
import world.World;
import world.WorldHex;
import world.WorldSquare;

import javax.swing.*;
import java.awt.*;
import java.util.List;

public class GameWindow extends JFrame implements EventLoggerListener {
    private final String mapType;
    private final int width;
    private final int height;
    private World world;
    private final JTextArea logTextArea;
    private final GameBoard gameBoard; // Changed to GameBoard interface

    public GameWindow(String mapType, int width, int height) {
        this.mapType = mapType;
        this.width = width;
        this.height = height;

        setTitle("Gra: " + (mapType.equals("hex") ? "Hex" : "Szachownica") + " Filip Grela 203850");
        setSize(600, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());

        // Menu bar
        JMenuBar menuBar = new JMenuBar();
        JMenu gameMenu = new JMenu("Game");
        JMenuItem loadItem = new JMenuItem("Load Game");
        JMenuItem saveItem = new JMenuItem("Save Game");
        gameMenu.add(loadItem);
        gameMenu.add(saveItem);
        menuBar.add(gameMenu);
        setJMenuBar(menuBar);

        // Add action listeners for menu items
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
                if (!filename.endsWith(".json")) filename += ".json";
                saveManager.SaveManager.saveWorldToFile(world, "saves/" + filename);
                JOptionPane.showMessageDialog(this, "Game saved as " + filename);
            }
        });

        // Initialize world
        world = mapType.equals("hex") ? new WorldHex(width, height) : new WorldSquare(width, height);

        // Game board
        gameBoard = mapType.equals("hex")
            ? new GameBoardHex(width, height, world)
            : new GameBoardSquare(width, height, world);
        add((JPanel) gameBoard, BorderLayout.CENTER);

        // Log panel
        JPanel logPanel = new JPanel();
        logPanel.setPreferredSize(new Dimension(800, 200)); // 1/3 of the window height
        logPanel.setLayout(new BorderLayout());
        logPanel.setBackground(Color.WHITE);

        // Search panel
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

        // Search field listener
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
        drawWorld();
    }

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

    public void drawWorld() {
        gameBoard.drawWorld();
    }

    public void refresh() {
        drawWorld();
    }

    public World getWorld() {
        return world;
    }
}
