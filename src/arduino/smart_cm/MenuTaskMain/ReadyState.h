#ifndef __READY_STATE__
#define __READY_STATE__

#include "ButtonImpl.h"

class ReadyState {
  public:
    ReadyState();
    void initButtonsReady();
    void readyMessage();

  private:
    ButtonImpl* btnUp;
    ButtonImpl* btnDown;
};

#endif
