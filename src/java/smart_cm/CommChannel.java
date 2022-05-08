/**
 * Simple interface for an async msg communication channel
 * @author aricci
 *
 */
public interface CommChannel {

    /**
     * Send a message represented by a string (without new line).
     *
     * Asynchronous model.
     *
     * @param msg to receive from channel communication
     */
    void sendMsg(String msg);

    /**
     * To receive a message.
     *
     * Blocking behaviour.
     */
    String receiveMsg() throws InterruptedException;

    /**
     * Checks if a message is available.
     *
     * @return true if a message is available
     */
    boolean isMsgAvailable();
}
