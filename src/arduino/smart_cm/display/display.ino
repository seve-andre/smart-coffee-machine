#include <LiquidCrystal_I2C.h>
#include <EnableInterrupt.h>
#include "State.h"
#include "Timer.h"
#include "Indent.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

//Sezione Timer
Timer* timerTest1;

//Sezione BTN
int btn_up = 4;
int btn_down = 5;
int btn_selection = 6;

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

void setup() {
  //Serial.begin(9600);
  //lcd.init();
  //lcd.backlight();
  
  //rowIndent = new Indent();
  //enableInterrupt(btn_selection, selectBeverage, FALLING);
  //enableInterrupt(btn_down, moveDown, RISING);
  //enableInterrupt(btn_up, moveUp, RISING);

  n_thea = 5;
  n_coffee = 5;
  n_chocolate = 5;
  
  isPrint = true;
  isAssistanceRequired = false;
  isAssistanceRequiredPrint = false;

  timerIdle = millis();
}

void loop() {
  returnToReadyState();
  lcd.setCursor(2, 2);
  menuOption = rowIndent->getPositionIndent();

  if (n_thea == 0 || n_chocolate == 0 || n_coffee == 0) {
    isAssistanceRequired = true;
    assistanceRequired();
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

void moveUp() {
  timerIdle = millis();
  rowIndent->moveUp();
  isPrint = true;
  Serial.println(rowIndent->getPositionIndent());
}

void moveDown() {
  timerIdle = millis();  
  rowIndent->moveDown();
  isPrint = true;
  Serial.println(rowIndent->getPositionIndent());
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

void assistanceRequired() {
  if (!isAssistanceRequiredPrint) {
    isAssistanceRequiredPrint = true;
    lcd.clear();
    lcd.print("Assistance Required");
  }
}

void returnToReadyState() {
  static unsigned long dt; 

  dt = millis() - timerIdle;
  
  //scatta l'interrupt
  if (dt >= 5000 && !isAssistanceRequired) {
      timerIdle = millis();
      lcd.clear();
      lcd.print("Return to READY");
  }
}
