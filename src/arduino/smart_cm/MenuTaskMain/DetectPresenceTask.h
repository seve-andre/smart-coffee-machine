#include "Task.h"

#define T_IDLE 60000

class DetectPresenceTask: public Task {
  public:
    DetectPresenceTask();
    void tick();

  private:
    bool isUserDetected();
};
