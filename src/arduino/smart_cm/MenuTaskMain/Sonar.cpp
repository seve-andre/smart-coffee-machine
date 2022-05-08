#include "Sonar.h"
#include "Arduino.h"
#include "Lcd.h"
#include "DetectDrinkTakenTask.h"

Sonar::Sonar() {
  pinMode(trigPort, OUTPUT);
  pinMode(echoPort, INPUT);
}

float Sonar::getSoundSpeed() {
  return 331.5 + 0.6*temperature;   
}

bool Sonar::isDrinkTaken() {
  return (getDistance() >= MAX_DISTANCE);
}

float Sonar::getDistance() {
    digitalWrite(trigPort,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPort,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPort,LOW);

    long tUS = pulseInLong(echoPort, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*getSoundSpeed();

    delay(50);

    //controllo valori di jitter
    if (d < 0.04 || d > 10.0) {
      d = 0.00;
    }
    
    return d;
}

void Sonar::initializeTimer() {
  timerTimeOut = millis();
}

void Sonar::timeTimeout() {
  static unsigned long dt;

  dt = millis() - timerTimeOut;

  //Interrupt
  if (dt >= Ttimeout || isDrinkTaken()) {
      Serial.println("machine goes on");
      timerTimeOut = millis();
      Lcd::getInstance()->clear();
      //Andare in un altro Stato
      CoffeeMachine::goToWorkingState(DRINK_TAKEN);
  }
}
