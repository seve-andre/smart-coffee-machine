#include "Beverage.h"
#include "BootMain.h"

Beverage::Beverage() {
  this->n_coffee = 5;
  this->n_thea = 5;
  this->n_chocolate = 5;
}

Beverage::Beverage(unsigned int n_coffee, unsigned int n_thea, unsigned int n_chocolate) {
  this->n_coffee = n_coffee;
  this->n_thea = n_thea;
  this->n_chocolate = n_chocolate;
}

void Beverage::takeACoffee() {
  if (n_coffee < 1) {
    n_coffee = 0;
  } else {
    n_coffee--;
  }
}

void Beverage::takeAThea() {
  if (n_thea < 1) {
    n_thea = 0;
  } else {
    n_thea--;
  }
}

void Beverage::takeAChocolate() {
  if (n_chocolate < 1) {
    n_chocolate = 0;
  } else {
    n_chocolate--;
  }
}

unsigned int Beverage::getNCoffee() {
  return this->n_coffee;
}

unsigned int Beverage::getNThea() {
  return this->n_thea;  
}

unsigned int Beverage::getNChocolate() {
  return this->n_chocolate;
}

void Beverage::printCoffeeMessage() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("making a coffee");
}

void Beverage::printTheaMessage() {
  lcd.clear(); 
  lcd.setCursor(0, 1);
  lcd.print("making a tea");
}

void Beverage::printChocolateMessage() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("making a chocolate");
}
