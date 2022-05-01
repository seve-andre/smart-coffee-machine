#ifndef __SONAR_TASK__
#define __SONAR_TASK__

#include "DetectDrinkTakenTask.h"
#include "Sonar.h"
#include "Task.h"

class DetectDrinkTakenTask : public Task {
  public:
    DetectDrinkTakenTask();
    void tick();
    void checkTimeTimeout();

  private:
  Sonar* proximitySensor;
};

#endif
