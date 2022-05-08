public class ArduinoCommunicator {

    CommChannel channel;
    SmartCoffeeMachine coffeeMachine;

    public ArduinoCommunicator(CommChannel channel, SmartCoffeeMachine coffeeMachine) {
        this.coffeeMachine = coffeeMachine;
        this.channel = channel;
    }

    public void start() {
        while (true) {
            try {
                String msg = channel.receiveMsg();
                if (msg.equals("idle")) {
                    coffeeMachine.setModality(CoffeeMachineState.IDLE);
                } else if (msg.equals("working")) {
                    coffeeMachine.setModality(CoffeeMachineState.WORKING);
                } else if (msg.equals("assistance")) {
                    coffeeMachine.setModality(CoffeeMachineState.ASSISTANCE);
                    coffeeMachine.enableAssistance();
                } else if (msg.equals("recovery")) {
                    coffeeMachine.setModality(CoffeeMachineState.RECOVERY);
                    coffeeMachine.enableRecovery();
                } else if (msg.equals("")) {
                    coffeeMachine.setProducts("1", "2", "3");
                }
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
    }

}
