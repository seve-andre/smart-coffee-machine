#ifndef __SONAR__
#define __SONAR__


#define NO_OBJ_DETECTED -1
#define OBJ_DETECTED 1
#define MAX_DISTANCE 0.41

class Sonar {

public:  
  Sonar(int echoPort, int trigPort);
  bool isDrinkTaken();

private:
    const float vs = 331.5 + 0.6*20;
    float getSoundSpeed();
    float getDistance();
    
    float temperature;    
    int echoPort, trigPort;
};

#endif 
