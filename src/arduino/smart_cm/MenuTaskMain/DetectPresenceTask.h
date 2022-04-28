#include "Task.h"

class DetectPresenceTask: public Task {
  public:
    DetectPresenceTask();
    void tick();

  private:
    bool isUserDetected();
};
