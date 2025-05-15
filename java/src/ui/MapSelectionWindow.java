package ui;

import constants.Constants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MapSelectionWindow extends JFrame {
    // --- DODANE: callback do obsługi wyboru mapy ---
    public interface OnMapSelectedListener {
        void onMapSelected(String mapType, int width, int height);
    }
    private OnMapSelectedListener onMapSelectedListener;

    public void setOnMapSelected(OnMapSelectedListener listener) {
        this.onMapSelectedListener = listener;
    }
    // ------------------------------------------------

    public MapSelectionWindow() {
        setTitle("Wybór mapy");
        setSize(400, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(2, 1));

        JButton hexButton = new JButton("Hex");
        JButton chessButton = new JButton("Szachownica");

        ActionListener mapSelectListener = e -> {
            String mapType;
            int defaultWidth, defaultHeight;
            if (e.getSource() == hexButton) {
                mapType = "hex";
                defaultWidth = 20;
                defaultHeight = 20;
            } else {
                mapType = "chess";
                defaultWidth = Constants.Map.Chessboard.DefaultWidth;
                defaultHeight = Constants.Map.Chessboard.DefaultHeight;
            }

            JTextField widthField = new JTextField(String.valueOf(defaultWidth));
            JTextField heightField = new JTextField(String.valueOf(defaultHeight));
            JPanel inputPanel = new JPanel(new GridLayout(2,2));
            inputPanel.add(new JLabel("Szerokość:"));
            inputPanel.add(widthField);
            inputPanel.add(new JLabel("Wysokość:"));
            inputPanel.add(heightField);

            int result = JOptionPane.showConfirmDialog(
                MapSelectionWindow.this,
                inputPanel,
                "Podaj wymiary planszy",
                JOptionPane.OK_CANCEL_OPTION
            );
            if (result == JOptionPane.OK_OPTION) {
                try {
                    int width = Integer.parseInt(widthField.getText());
                    int height = Integer.parseInt(heightField.getText());
                    if (width > 0 && height > 0) {
                        if (onMapSelectedListener != null) {
                            onMapSelectedListener.onMapSelected(mapType, width, height);
                        }
                    } else {
                        JOptionPane.showMessageDialog(MapSelectionWindow.this, "Podaj dodatnie liczby!", "Błąd", JOptionPane.ERROR_MESSAGE);
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(MapSelectionWindow.this, "Nieprawidłowe liczby!", "Błąd", JOptionPane.ERROR_MESSAGE);
                }
            }
        };

        hexButton.addActionListener(mapSelectListener);
        chessButton.addActionListener(mapSelectListener);

        panel.add(hexButton);
        panel.add(chessButton);

        add(panel);
    }
}
