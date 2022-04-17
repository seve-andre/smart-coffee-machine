#ifndef __ASSISTANCE__
#define __ASSISTANCE__

class Assistance {
  public:
    Assistance();
    void assistanceRequired();
    bool getAssistanceStatus();

  private:
    bool isAssistanceRequiredPrint;
    bool isAssistanceTriggered;
};

#endif
