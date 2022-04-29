#include "State.h"
#include "WorkingState.h";

class CoffeeMachine {
  private:
    void startWorking();
    void goToSleep();
    void doSelfTest();
    
  public:
    CoffeeMachine();
    void doState();
    static void goToState(WorkingState newState);
};
