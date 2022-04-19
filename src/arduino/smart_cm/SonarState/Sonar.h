#ifndef __SONAR__
#define __SONAR__


#define NO_OBJ_DETECTED -1
#define OBJ_CLOSE -2

class Sonar {

public:  
  Sonar(int echoPort, int trigPort, long maxTime);
  float getDistance();

private:
    const float vs = 331.5 + 0.6*20;
    float getSoundSpeed();
    
    float temperature;    
    int echoPort, trigPort;
    long timeOut;
};

#endif 
