import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionListener;

public class SmartCoffeeMachine extends JFrame {
    private static final int WIDTH = 500;
    private static final int HEIGHT = 500;
    private static final String PROGRAM_TITLE = "Smart Coffee Machine";

    private final JLabel lblModality;
    private final JButton btnRefill;
    private final JButton btnRecover;

    private final JLabel lblNCoffee;
    private final JLabel lblNTea;
    private final JLabel lblNChocolate;

    private final JLabel lblNSelfTest;
    private int selfTestsCount = 0;

    public SmartCoffeeMachine(CommChannel channel) {
        GuiFactory guiFactory = new GuiFactory();

        // header with title
        JPanel titlePanel = new JPanel();
        JLabel lblProgramName = guiFactory.createTitle(PROGRAM_TITLE);
        titlePanel.add(lblProgramName);

        // central content with labels
        JPanel labelsPanel = new JPanel(new GridLayout(3, 3));
        labelsPanel.setBorder(new EmptyBorder(0, 80, 0, 80));
        lblModality = new JLabel("Modality: IDLE");
        lblNCoffee = new JLabel();
        lblNTea = new JLabel();
        lblNChocolate = new JLabel();
        lblNSelfTest = new JLabel();

        labelsPanel.add(lblModality);
        labelsPanel.add(lblNSelfTest);
        labelsPanel.add(lblNCoffee);
        labelsPanel.add(lblNTea);
        labelsPanel.add(lblNChocolate);

        // footer with buttons
        JPanel buttonsPanel = new JPanel();
        btnRefill = guiFactory.createPrimaryButton("Refill");
        btnRecover = guiFactory.createPrimaryButton("Recover");

        // initially refill and recover are not needed, so their visibility is set to false
        btnRefill.setEnabled(false);
        btnRecover.setEnabled(false);

        ActionListener actionRefill = e -> {
            channel.sendMsg("Refill");
            this.setProducts("5", "5", "5");
            btnRefill.setEnabled(false);
        };
        ActionListener actionRecover = e -> {
            channel.sendMsg("Recover");
            btnRecover.setEnabled(false);
        };

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

    public void setModality(CoffeeMachineState state) {
        SwingUtilities.invokeLater(() -> lblModality.setText("Modality: " + state.name()));
    }

    public void enableAssistance() {
        btnRefill.setEnabled(true);
    }

    public void enableSelfTest() {
        btnRecover.setEnabled(true);
        selfTestsCount++;
        setSelfTests();
    }

    private void setSelfTests() {
        lblNSelfTest.setText("N° self test: " + selfTestsCount);
    }

    public void setProducts(String coffeeQuantity, String teaQuantity, String chocolateQuantity) {
        SwingUtilities.invokeLater(() -> {
            lblNCoffee.setText("N° Coffee: " + coffeeQuantity);
            lblNTea.setText("N° Tea: " + teaQuantity);
            lblNChocolate.setText("N° Chocolate: " + chocolateQuantity);
        });
    }

    public void reduceQuantity(String product) {
        String currentQuantity;
        int currentValue;

        switch (product) {
            case "Tea":
                currentQuantity = lblNTea.getText();
                currentValue = Integer.parseInt(currentQuantity.substring(currentQuantity.length() - 1));
                this.setTeaQuantity(currentValue - 1);
                break;
            case "Coffee":
                currentQuantity = lblNCoffee.getText();
                currentValue = Integer.parseInt(currentQuantity.substring(currentQuantity.length() - 1));
                this.setCoffeeQuantity(currentValue - 1);
                break;
            case "Chocolate":
                currentQuantity = lblNChocolate.getText();
                currentValue = Integer.parseInt(currentQuantity.substring(currentQuantity.length() - 1));
                this.setChocolateQuantity(currentValue - 1);
                break;
        }
    }

    private void setTeaQuantity(int teaQuantity) {
        SwingUtilities.invokeLater(() -> lblNTea.setText("N° Tea: " + teaQuantity));
    }

    private void setCoffeeQuantity(int coffeeQuantity) {
        SwingUtilities.invokeLater(() -> lblNCoffee.setText("N° Coffee: " + coffeeQuantity));
    }

    private void setChocolateQuantity(int chocolateQuantity) {
        SwingUtilities.invokeLater(() -> lblNChocolate.setText("N° Chocolate: " + chocolateQuantity));
    }
}
