#include "MenuSelector.h"
#include "Arduino.h"
#include "Drink.h"
#include "ButtonImpl.h"
#include "CoffeeMachine.h"
#include "Lcd.h"

ButtonImpl* btnUp;
ButtonImpl* btnDown;
ButtonImpl* btnMake;

unsigned long timerIdle;

bool btnUpClick;
bool btnDownClick;
Lcd* lcd;

Drink::Type drinks[3] = {
  Drink::Coffee,
  Drink::Tea,
  Drink::Chocolate
};

MenuSelector::MenuSelector() {
  btnUp = new ButtonImpl(4);
  btnDown = new ButtonImpl(5);
  btnMake = new ButtonImpl(6);

  lcd = Lcd::getInstance();
  
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

Drink::Type MenuSelector::getSelected() {
  return drinks[currentSelection];
}

void MenuSelector::printSelection() {
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
    CoffeeMachine::goToState(WorkingState::MAKE_DRINK);
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
}

void MenuSelector::returnToReadyState() {  
  //Interrupt
  if ((millis() - timerIdle) >= 5000) { //&& !isAssistanceRequired && readyState == 2) {
      timerIdle = millis();
      lcd->clear();
      CoffeeMachine::goToState(WorkingState::READY);
  }
}
