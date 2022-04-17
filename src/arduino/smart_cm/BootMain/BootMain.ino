#include <LiquidCrystal_I2C.h>
#include <EnableInterrupt.h>
#include "BootMain.h"
#include "Boot.h"
#include "Ready.h"
#include "Indent.h"
#include "Assistance.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

Boot* bootMachine;
Ready* readyMachine;
Assistance* ast;

int btn_up = 4;
int btn_down = 5;
int btn_selection = 6;

unsigned int readyState;

//State-2
//Sezione LCD
const int colIndent = 0;
Indent* rowIndent;

//Sezione beverage
unsigned int n_coffee;
unsigned int n_thea;
unsigned int n_chocolate;
unsigned long timerIdle;
unsigned int menuOption;

boolean isCoffeeActive;
boolean isTheaActive;
boolean isChocolateActive;
boolean isPrint;
boolean isAssistanceRequired;
boolean isAssistanceRequiredPrint;
boolean isMenuInitialize;

void setup() {
  Serial.begin(9600);
  //lcd initialization
  lcd.init();
  lcd.backlight();
  
  bootMachine = new Boot();
  readyMachine = new Ready();
  rowIndent = new Indent();
  ast = new Assistance();

  readyState = 0;
  isMenuInitialize = false;
}

void loop() {  
  switch(readyState) {
    case 0:
      bootButtonIntialization();
      bootMachine->initialization();
    break;

    case 1:
      bootButtonIntialization();
      readyMachine->showReadyMessage();
      isMenuInitialize = false;
    break;

    case 2:
      menuInitialization();
      loopMenu();
    break;

    case 3:
      isAssistanceRequired = true;
      ast->assistanceRequired();
    break;
  }
}

void bootButtonIntialization() {
  enableInterrupt(btn_selection, goToMenuState, RISING);
  enableInterrupt(btn_down, goToMenuState, RISING);
  enableInterrupt(btn_up, goToMenuState, RISING);  
}

void goToMenuState() {
  if (bootMachine->isInitializationComplete()) {
    readyState = 2;
  }
}

//State-2
//-------------------------------

void loopMenu() {
  returnToReadyState();
  lcd.setCursor(2, 2);
  menuOption = rowIndent->getPositionIndent();

  if (n_thea == 0 || n_chocolate == 0 || n_coffee == 0) {
    readyState = 3;
  }

  if (!isAssistanceRequired) {
    switch(menuOption) {
      case 0:
        if (isPrint) {
          isPrint = false;
          lcd.clear();
          lcd.print("making a coffee");
        }
      break;

      case 1:
        if (isPrint) {
          isPrint = false;
          lcd.clear(); 
          lcd.print("making a tea");
        }
      break;

      case 2:
        if (isPrint) {
          isPrint = false;
          lcd.clear();
          lcd.print("making a chocolate");
        }
      break;
    }
  }
}

void menuInitialization() {
  if (!isMenuInitialize) {
    enableInterrupt(btn_selection, selectBeverage, FALLING);
    enableInterrupt(btn_down, moveDown, RISING);
    enableInterrupt(btn_up, moveUp, RISING);

    //Da inserire in altro metodo separato  
    n_thea = 5;
    n_coffee = 5;
    n_chocolate = 5;
  
    isPrint = true;
    isAssistanceRequired = false;
    isAssistanceRequiredPrint = false;

    timerIdle = millis();
    isMenuInitialize = true;
  }
}

void moveUp() {
  timerIdle = millis();
  rowIndent->moveUp();
  isPrint = true;
}

void moveDown() {
  timerIdle = millis();  
  rowIndent->moveDown();
  isPrint = true;
}

void selectBeverage() {
  timerIdle = millis();
  menuOption = rowIndent->getPositionIndent();
  int buttonSelection = digitalRead(btn_selection);

  delay(50);
  if (buttonSelection == LOW) {
    switch(menuOption) {
      case 0:
        if (n_coffee < 1) {
          n_coffee = 0;
        } else {
          n_coffee--;
        }
      break;
    
      case 1:
        if (n_thea < 1) {
          n_thea = 0;
        } else {
          n_thea--;
        }
      break;

      case 2:
        if (n_chocolate < 1) {
          n_chocolate = 0;
        } else {
          n_chocolate--;
        }
      break;
    }
  }
}

//void assistanceRequired() {
//  if (!isAssistanceRequiredPrint) {
//    isAssistanceRequiredPrint = true;
//    lcd.clear();
//    lcd.print("Assistance Required");
//  }
//}

void returnToReadyState() {
  static unsigned long dt; 

  dt = millis() - timerIdle;
  
  //scatta l'interrupt
  if (dt >= 5000 && !isAssistanceRequired) {
      timerIdle = millis();
      lcd.clear();
      readyMachine->resetIsFirstReady();
      readyState = 1;
  }
}
