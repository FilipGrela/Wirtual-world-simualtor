package ui;

import javax.swing.*;
import java.awt.event.ActionListener;

public class OrganismAddDialog {
    public static void showOrganismSelection(JComponent parent, String[] organisms, int x, int y, ActionListener onOrganismSelected) {
        JPopupMenu menu = new JPopupMenu();
        for (String organism : organisms) {
            JMenuItem item = new JMenuItem(organism);
            item.addActionListener(e -> {
                // Pass the selected organism to the listener
                item.putClientProperty("organism", organism);
                item.putClientProperty("x", x);
                item.putClientProperty("y", y);
                onOrganismSelected.actionPerformed(e);
            });
            menu.add(item);
        }
        menu.show(parent, x, y);
    }
}