package ui;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Path2D;

public class HexButton extends JButton {
    private Shape hexShape;

    public HexButton() {
        setContentAreaFilled(false);
        setFocusPainted(false);
        setBorderPainted(false);
        setOpaque(false);
    }

    private void updateHexShape(int width, int height) {
        int w = width - 1;
        int h = height - 1;
        int r = Math.min(w, h) / 2;
        int centerX = w / 2;
        int centerY = h / 2;
        Path2D hex = new Path2D.Double();
        for (int i = 0; i < 6; i++) {
            double angle = Math.PI / 3.0 * i - Math.PI / 6.0;
            int x = centerX + (int) (r * Math.cos(angle));
            int y = centerY + (int) (r * Math.sin(angle));
            if (i == 0) hex.moveTo(x, y);
            else hex.lineTo(x, y);
        }
        hex.closePath();
        hexShape = hex;
    }

    @Override
    protected void paintComponent(Graphics g) {
        if (hexShape == null || !hexShape.getBounds().equals(getBounds())) {
            updateHexShape(getWidth(), getHeight());
        }
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        g2.setColor(getBackground());
        g2.fill(hexShape);
        g2.setColor(getForeground());
        g2.draw(hexShape);
        // Draw text/icon centered
        if (getIcon() != null) {
            int x = (getWidth() - getIcon().getIconWidth()) / 2;
            int y = (getHeight() - getIcon().getIconHeight()) / 2;
            getIcon().paintIcon(this, g2, x, y);
        }
        String text = getText();
        if (text != null && !text.isEmpty()) {
            FontMetrics fm = g2.getFontMetrics();
            int x = (getWidth() - fm.stringWidth(text)) / 2;
            int y = (getHeight() + fm.getAscent() - fm.getDescent()) / 2;
            g2.setColor(getForeground());
            g2.drawString(text, x, y);
        }
        g2.dispose();
    }

    @Override
    protected void paintBorder(Graphics g) {
        if (hexShape == null || !hexShape.getBounds().equals(getBounds())) {
            updateHexShape(getWidth(), getHeight());
        }
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setColor(getForeground());
        g2.draw(hexShape);
        g2.dispose();
    }

    @Override
    public boolean contains(int x, int y) {
        if (hexShape == null || !hexShape.getBounds().equals(getBounds())) {
            updateHexShape(getWidth(), getHeight());
        }
        return hexShape.contains(x, y);
    }
}