#ifndef __STATE__
#define __STATE__



class State {

  public:
  virtual void do() = 0;
  virtual void nextState() State;
}

#endif
