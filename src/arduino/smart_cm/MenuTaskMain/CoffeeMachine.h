#include "State.h"

class CoffeeMachine {
  private:
    CoffeeMachine();
    void startWorking();
    void goToSleep();
    void doSelfTest();
    
  public:  
    void setMachineState(MachineState newState);
};
