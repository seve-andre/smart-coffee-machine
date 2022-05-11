#ifndef __PIR__
#define __PIR__

class Pir {
 
public: 
  Pir(int pin);
  bool isDetected();
//  void calibrate();

private:
  int pin;
};

#endif
