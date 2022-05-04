#ifndef __POT__
#define __POT__

class Potentiometer {
 
public: 
  Potentiometer(int pin);
  unsigned int getValue();

private:
  int pin;

};

#endif
