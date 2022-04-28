#include "MenuSelector.h"
#include "Arduino.h"
#include "Drink.h"
#include "ButtonImpl.h"
#include "CoffeeMachine.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
ButtonImpl* btnUp;
ButtonImpl* btnDown;
ButtonImpl* btnMake;

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
}

void MenuSelector::moveNext() {
  if (currentSelection < maxNSelection) {
    currentSelection++;
  }
}

void MenuSelector::movePrev() {
  if (currentSelection > 0) {
      currentSelection--;
  }
}

void MenuSelector::printSelection() {
  lcd.clear();

  // resolve long press detection
  if (btnDown->isPressed()) {
    moveNext();
  } else if (btnUp->isPressed()) {
    movePrev();
  } else if (btnMake->isPressed()) {
    CoffeeMachine::nextWorkingState();
    return;
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
