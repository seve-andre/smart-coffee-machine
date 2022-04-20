import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class CaffeMachineGui extends JFrame {
    private final int WIDTH = 500;
    private final int HEIGHT = 500;
    private final int GRID_WIDTH = 5;
    private final int GRID_HEIGHT = 5;

    private JButton btnRefill;
    private JButton btnRecover;
    private JLabel lblModality;
    private JLabel lblNCoffee;
    private JLabel lblNThea;
    private JLabel lblNChocolate;
    private JLabel lblNSelfTest;

    public CaffeMachineGui() {
        btnRefill = new JButton("Refill");
        btnRecover = new JButton("Recover");
        lblModality = new JLabel("Modality");
        lblNCoffee = new JLabel("N Coffee:");
        lblNThea = new JLabel("N Thea:");
        lblNChocolate = new JLabel("N Chocolate");
        lblNSelfTest = new JLabel("N Self-Test:");

        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(WIDTH, HEIGHT);

        JPanel panel = new JPanel(new GridLayout(GRID_HEIGHT, GRID_WIDTH));
        this.getContentPane().add(panel);

        ActionListener actionRefill = e -> {
            System.out.println("Refill Mode");
        };

        ActionListener actionRecover = e -> {
            System.out.println("Recover Mode");
        };

        btnRefill.addActionListener(actionRefill);
        btnRecover.addActionListener(actionRecover);

        panel.add(btnRefill);
        panel.add(btnRecover);
        panel.add(lblModality);
        panel.add(lblNCoffee);
        panel.add(lblNThea);
        panel.add(lblNChocolate);
        panel.add(lblNSelfTest);

        this.setVisible(true);
    }

    public static void main(String[] args) {
        new CaffeMachineGui();
    }
}
