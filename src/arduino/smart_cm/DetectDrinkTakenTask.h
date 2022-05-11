#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "Sonar.h"
#include "Task.h"

extern bool isSonarActive;
extern bool firstTime;

class DetectDrinkTakenTask : public Task {
  public:
    DetectDrinkTakenTask();
    void tick();
    void checkTimeTimeout();
    
  private:
    Sonar* proximitySensor;
};

#endif
