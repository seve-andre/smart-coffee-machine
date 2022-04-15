#ifndef __BOOT__
#define __BOOT__

class Boot {
  public:
    Boot();
    void showWelcomeMessage();
    void pauseBoot();
    void initialization();
    bool isInitializationComplete();

  private:
    unsigned int timePauseBoot;
    unsigned int n_thea;
    unsigned int n_coffee;
    unsigned int n_chocolate;
    
    bool isWelcomeMessageShow;
    bool isReadyMessageShow;
    bool initializationStatus;
};

#endif
