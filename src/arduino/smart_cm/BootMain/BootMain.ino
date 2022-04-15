#include <EnableInterrupt.h>
#include "BootMain.h"
#include "Boot.h"
#include "Ready.h"

unsigned int readyState;

Boot* bootMachine;
Ready* readyMachine;

int btn_up = 4;
int btn_down = 5;
int btn_selection = 6;

void setup() {
  Serial.begin(9600);

  readyState = 0;
  bootMachine = new Boot();
  readyMachine = new Ready();

  enableInterrupt(btn_selection, goToMenuState, RISING);
  enableInterrupt(btn_down, goToMenuState, RISING);
  enableInterrupt(btn_up, goToMenuState, RISING);
}

void loop() {  
  switch(readyState) {
    case 0:
      bootMachine->initialization();
    break;

    case 1:
      readyMachine->showReadyMessage();
    break;

    case 2:
      Serial.println("Stato MENU");
    break;
  }
}

void goToMenuState() {
  if (bootMachine->isInitializationComplete()) {
    readyState = 2;
  }
}
