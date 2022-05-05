#include "Timer.h"
#include <avr/sleep.h>
#include <PinChangeInterrupt.h>

unsigned long Tidle;
bool userDetected;

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);

  attachPCINT(digitalPinToPCINT(10), wakeUpNow, RISING);
}

void loop() {
  int pir = digitalRead(10);
  userDetected = pir;  
  
  timeBeforePause();
  // Serial.println("Arduino ATTIVO");
}

//Arduino si risveglia
void wakeUpNow() {
  sleep_disable();
  Tidle = millis();
  Serial.println("SLEEP_MODE_OFF");
}

//Arduino va in sleep-mode
void sleepNow() {
  Serial.println("SLEEP_MODE_ON");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}

//vai in pausa dopo 5s di attesa.
void timeBeforePause() {
  static unsigned long dt; 
  int ret = 0;

  dt = millis() - Tidle;

  //Interrupt
  if (dt >= 5000 && !userDetected) {
      Serial.println("user not detected, go to sleep");
      Tidle = millis();
      sleepNow();
  }
}
