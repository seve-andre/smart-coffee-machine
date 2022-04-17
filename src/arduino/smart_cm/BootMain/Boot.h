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
    int btn_up;
    int btn_down;
    int btn_selection;
  
    unsigned int timePauseBoot;
    unsigned int n_thea;
    unsigned int n_coffee;
    unsigned int n_chocolate;
    
    bool isWelcomeMessageShow;
    bool isReadyMessageShow;
    bool initializationStatus;
};

#endif
