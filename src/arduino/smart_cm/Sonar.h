#ifndef __SONAR__
#define __SONAR__

#define NO_OBJ_DETECTED -1
#define OBJ_DETECTED 1
#define MAX_DISTANCE 0.41

#include "CoffeeMachine.h"

class Sonar {

public:  
  Sonar();
  bool isDrinkTaken();
  float getDistance();
  void initializeTimer();
  void timeTimeout();

private:
    const float vs = 331.5 + 0.6*20;
    float getSoundSpeed();
    float temperature;
    unsigned int timerTimeOut;  
    
    const int trigPort = 9;
    const int echoPort = 8;
    const unsigned long Ttimeout = 5000;
};

#endif 
