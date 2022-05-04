#include "MenuSelector.h"
#include "Arduino.h"
#include "Drink.h"
#include "ButtonImpl.h"
#include "CoffeeMachine.h"
#include "BeverageStore.h"
#include "Lcd.h"
#include "Pot.h"

Potentiometer* potSugar;

unsigned long timerIdle;

bool btnUpClick;
bool btnDownClick;

BeverageStore* beverages;
Lcd* lcd;

Drink::Type drinks[3] = {
  Drink::Coffee,
  Drink::Tea,
  Drink::Chocolate
};

MenuSelector::MenuSelector() {
  beverages = new BeverageStore(1,1,0);
  potSugar = new Potentiometer(2);
  
  btnUp = new ButtonImpl(4);
  btnDown = new ButtonImpl(5);
  btnMake = new ButtonImpl(6);

  lcd = Lcd::getInstance();
  
  this->currentSelection = 0;
}

void MenuSelector::restartTimerIdle() {
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

Drink::Type MenuSelector::getSelected() {
  return drinks[currentSelection];
}

bool MenuSelector::drinksAvailable() {
  return beverages->getQuantity(Drink::Coffee) > 0 
  || beverages->getQuantity(Drink::Tea) > 0
  || beverages->getQuantity(Drink::Chocolate) > 0;
}

void MenuSelector::printSelection() {
  if (!drinksAvailable()) {
    CoffeeMachine::goToMachineState(ASSISTANCE);
    CoffeeMachine::goToWorkingState(READY);
  } else {
    delay(50);
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
      beverages->reduceQuantity(getSelected());
      CoffeeMachine::goToWorkingState(WorkingState::MAKE_DRINK);
      return;
    } else if (!btnDown->isPressed()) {
      btnDownClick = false;
    } if (!btnUp->isPressed()) {
      btnUpClick = false;
    }
  
    char drinkMessage[10];
  
    switch (drinks[currentSelection]) {
      case Drink::Coffee:
        strcpy(drinkMessage, "Coffee");
      break;
      
      case Drink::Tea:
        strcpy(drinkMessage, "Tea");
      break;
      
      case Drink::Chocolate:
        strcpy(drinkMessage, "Chocolate");
      break;
    }
  
    lcd->print(drinkMessage);
    lcd->printAt(0,3, (String("Sugar level: ") + potSugar->getValue()).c_str());
  }
}

void MenuSelector::returnToReadyState() {  
  //Interrupt
  if ((millis() - timerIdle) >= 5000) { //&& !isAssistanceRequired && readyState == 2) {
      timerIdle = millis();
      lcd->clear();
      CoffeeMachine::goToWorkingState(WorkingState::READY);
  }
}
