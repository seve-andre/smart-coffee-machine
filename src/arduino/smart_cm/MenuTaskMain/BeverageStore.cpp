#include "BeverageStore.h"

#define DEFAULT_QUANTITY 5

BeverageStore::BeverageStore() {
  this->n_coffee = DEFAULT_QUANTITY;
  this->n_tea = DEFAULT_QUANTITY;
  this->n_chocolate = DEFAULT_QUANTITY;  
}

BeverageStore::BeverageStore(unsigned int n_coffee, unsigned int n_tea, unsigned int n_chocolate) {
  this->n_coffee = n_coffee;
  this->n_tea = n_tea;
  this->n_chocolate = n_chocolate;
}

void BeverageStore::reduceQuantity(Drink::Type drinkType) {
  switch(drinkType) {
    case Drink::Coffee: 
      this->n_coffee--;
    break;
    case Drink::Tea:
      this->n_tea--;
    break;
    case Drink::Chocolate:
      this->n_chocolate--;
    break;
  }
}

unsigned int BeverageStore::getQuantity(Drink::Type drinkType) {
  switch(drinkType) {
    case Drink::Coffee: 
      return this->n_coffee;
    break;
    case Drink::Tea:
      return this->n_tea;
    break;
    case Drink::Chocolate:
      return this->n_chocolate;
    break;
  }
}
