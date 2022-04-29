#include "MenuSelector.h"
#include "Arduino.h"
#include "Drink.h"
#include "ButtonImpl.h"
#include "CoffeeMachine.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
ButtonImpl* btnUp;
ButtonImpl* btnDown;
ButtonImpl* btnMake;

unsigned long timerIdle;

bool btnUpClick;
bool btnDownClick;

Drink::Type drinks[3] = {
  Drink::Coffee,
  Drink::Tea,
  Drink::Chocolate
};

MenuSelector::MenuSelector() {
  btnUp = new ButtonImpl(4);
  btnDown = new ButtonImpl(5);
  btnMake = new ButtonImpl(6);
  
  lcd.init();
  lcd.backlight();
  
  this->currentSelection = 0;
  timerIdle = millis();
}

void MenuSelector::moveNext() {
  timerIdle = millis();
  
  if (currentSelection < maxNSelection) {
    currentSelection++;
  }
}

void MenuSelector::movePrev() {
  timerIdle = millis();
  
  if (currentSelection > 0) {
      currentSelection--;
  }
}

void MenuSelector::printSelection() {
  lcd.clear();

  if (btnDown->isPressed()) {
    if (!btnDownClick) {
      btnDownClick = true;
      moveNext();
    }
  } else if (btnUp->isPressed()) {
    if (!btnUpClick) {
      btnUpClick = true;
      movePrev();
    }
  } else if (btnMake->isPressed()) {
    //CoffeeMachine::nextWorkingState();
    return;
  } else if (!btnDown->isPressed()) {
    btnDownClick = false;
  } if (!btnUp->isPressed()) {
    btnUpClick = false;
  }
  
  switch (drinks[currentSelection]) {
    case Drink::Coffee:
      lcd.setCursor(1,0);
      lcd.print("Coffee");
    break;
    
    case Drink::Tea:
     lcd.setCursor(1,0);
     lcd.print("Tea");
    break;
    
    case Drink::Chocolate:
     lcd.setCursor(1,0);
     lcd.print("Chocolate");
    break;
  }
}

void MenuSelector::returnToReadyState() {  
  //Interrupt
  if ((millis() - timerIdle) >= 5000) { //&& !isAssistanceRequired && readyState == 2) {
      timerIdle = millis();
      lcd.clear();
      CoffeeMachine::nextWorkingState();
      //readyMachine->resetIsFirstReady();
      //readyState = 1;
      //Serial.println("Ready");
  }
}
