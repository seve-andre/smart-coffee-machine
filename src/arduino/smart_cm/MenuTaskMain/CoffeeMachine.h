#ifndef __COFFEE_MACHINE__
#define __COFFEE_MACHINE__

#include "MachineState.h"
#include "WorkingState.h";

class CoffeeMachine {
  private:
    void startWorking();
    void goToSleep();
    void reactivateArduino();
    void doSelfTest();
    void printMessage(char msgToSend[]);
    WorkingState getState();
    
  public:
    CoffeeMachine();
    void doState();
    static void goToWorkingState(WorkingState newState);
    static void goToMachineState(MachineState newMachineState);
    static void resetServo();
};

#endif
