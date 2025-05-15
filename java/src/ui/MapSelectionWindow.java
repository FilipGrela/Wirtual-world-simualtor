package ui;

import constants.Constants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

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

        hexButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // Wywołaj callback jeśli ustawiony
                if (onMapSelectedListener != null) {
                    onMapSelectedListener.onMapSelected("hex", 20, 20);
                }
            }
        });

        chessButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JTextField widthField = new JTextField(String.valueOf(Constants.Map.Chessboard.DefaultWidth));
                JTextField heightField = new JTextField(String.valueOf(Constants.Map.Chessboard.DefaultHeight));
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
                            // Wywołaj callback jeśli ustawiony
                            if (onMapSelectedListener != null) {
                                onMapSelectedListener.onMapSelected("chess", width, height);
                            }
                        } else {
                            JOptionPane.showMessageDialog(MapSelectionWindow.this, "Podaj dodatnie liczby!", "Błąd", JOptionPane.ERROR_MESSAGE);
                        }
                    } catch (NumberFormatException ex) {
                        JOptionPane.showMessageDialog(MapSelectionWindow.this, "Nieprawidłowe liczby!", "Błąd", JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
        });

        panel.add(hexButton);
        panel.add(chessButton);

        add(panel);
    }

    // startGame nie jest już używane
}
