package smart_cm;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;

public class SmartCoffeeMachine extends JFrame {
    private static final int WIDTH = 500;
    private static final int HEIGHT = 500;
    private static final String PROGRAM_TITLE = "Smart Coffee Machine";

    public SmartCoffeeMachine() {
        GuiFactory guiFactory = new GuiFactory();

        // header with title
        JPanel titlePanel = new JPanel();
        JLabel lblProgramName = guiFactory.createTitle(PROGRAM_TITLE);
        titlePanel.add(lblProgramName);

        // central content with labels
        JPanel labelsPanel = new JPanel(new GridLayout(3, 3));
        labelsPanel.setBorder(new EmptyBorder(0, 80, 0, 80));
        JLabel lblModality = new JLabel("Modality: ");
        JLabel lblNCoffee = new JLabel("N° Coffee: ");
        JLabel lblNThea = new JLabel("N° Tea: ");
        JLabel lblNChocolate = new JLabel("N° Chocolate: ");
        JLabel lblNSelfTest = new JLabel("N° Self-Test: ");

        labelsPanel.add(lblModality);
        labelsPanel.add(lblNCoffee);
        labelsPanel.add(lblNThea);
        labelsPanel.add(lblNChocolate);
        labelsPanel.add(lblNSelfTest);

        // footer with buttons
        JPanel buttonsPanel = new JPanel();
        JButton btnRefill = guiFactory.createPrimaryButton("Refill");
        JButton btnRecover = guiFactory.createPrimaryButton("Recover");

        ActionListener actionRefill = e -> System.out.println("Refill Mode");
        ActionListener actionRecover = e -> System.out.println("Recover Mode");

        btnRefill.addActionListener(actionRefill);
        btnRecover.addActionListener(actionRecover);

        buttonsPanel.add(btnRefill);
        buttonsPanel.add(btnRecover);
        buttonsPanel.setPreferredSize(new Dimension(this.getWidth(), 100));

        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(WIDTH, HEIGHT);
        this.setTitle(PROGRAM_TITLE);

        this.add(titlePanel, BorderLayout.NORTH);
        this.add(labelsPanel, BorderLayout.CENTER);
        this.add(buttonsPanel, BorderLayout.SOUTH);

        // center window on run
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

    public static void main(String[] args) {
        new SmartCoffeeMachine();
    }
}
