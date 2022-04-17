#ifndef __READY__
#define __READY__

class Ready {
  public:
    Ready();
    void showReadyMessage();
    void resetIsFirstReady();

  private:
    boolean isFirstReady;
};

#endif
