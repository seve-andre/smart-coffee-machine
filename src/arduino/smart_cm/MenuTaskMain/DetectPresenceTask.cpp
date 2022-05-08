#include "DetectPresenceTask.h"
#include "Pir.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <PinChangeInterrupt.h>
#include "CoffeeMachine.h"

unsigned long Tsleep;
bool userDetected;
bool isInSleep;

//Arduino si risveglia
void wakeUpNow() {
  if (isInSleep) {
    sleep_disable();
    Tsleep = millis();
    Serial.println("SLEEP_MODE_OFF");
    isInSleep = false;
  }
}

//Arduino va in sleep-mode
void sleepNow() {
  Serial.println("SLEEP_MODE_ON");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  isInSleep = true;
}

// vai in pausa dopo 60s di attesa.
void timeSleep() {
  static unsigned long dt;

  dt = millis() - Tsleep;

  //Interrupt
  if (dt >= T_IDLE && !userDetected) {
      // Serial.println("user not detected, go to sleep");
      Tsleep = millis();
      delay(2000);
      sleepNow();
  }
}

Pir* presenceSensor;
CoffeeMachine* coffeeMachine;

DetectPresenceTask::DetectPresenceTask() {
  presenceSensor = new Pir(10);
  coffeeMachine = new CoffeeMachine();

  attachPCINT(digitalPinToPCINT(10), wakeUpNow, RISING);
  isInSleep = false;
}

bool DetectPresenceTask::isUserDetected() {
  return presenceSensor->isDetected();
}

void DetectPresenceTask::tick() {
  int pir = digitalRead(10);
  userDetected = pir;

  WorkingState currentState = coffeeMachine->getState();
  if (
    currentState == MENU_SELECTION
    || currentState == MAKE_DRINK
    || currentState == TAKE_DRINK
    || currentState == DRINK_TAKEN
  ) {
    userDetected = true;
    Tsleep = millis();
  }
  
  timeSleep();

  if (userDetected) {
    coffeeMachine->doState();
  }
}
