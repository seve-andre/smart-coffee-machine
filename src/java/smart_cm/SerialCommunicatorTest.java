public class SerialCommunicatorTest {

    public static void main(String[] args) throws Exception {
        SerialCommChannel channel = new SerialCommChannel("COM5", 9600);
        SmartCoffeeMachine machine = new SmartCoffeeMachine(channel);
        while (true) {
            if (channel.isMsgAvailable()) {
                String msg = channel.receiveMsg();
                System.out.println(msg);
                if (msg.contains("Quantity")) {
                    String[] cleanMsg = msg.split(":");

                    String[] quantities = cleanMsg[1].split(",");
                    machine.setProducts(quantities[0], quantities[1], quantities[2]);
                } else if (msg.equals("idle")) {
                    machine.setModality(CoffeeMachineState.IDLE);
                } else if (msg.equals("working")) {
                    machine.setModality(CoffeeMachineState.WORKING);
                } else if (msg.equals("assistance")) {
                    machine.setModality(CoffeeMachineState.ASSISTANCE);
                    machine.enableAssistance();
                } else if (msg.startsWith("REDUCE")) {
                    String[] reduceProduct = msg.split(" ");
                    machine.reduceQuantity(reduceProduct[1]);
                }
            }
        }
    }
}
