#include "DrinkFactory.h"
#include "Drink.h"
#include "Tea.cpp"
#include "Coffee.cpp"
#include "Chocolate.cpp"

Drink* DrinkFactory::makeDrink(Drink::Type drinkType) {
  switch(drinkType) {
    case Drink::Type::Tea:
      return new Tea();
      break;
    case Drink::Type::Coffee:
      return new Coffee();
      break;
    case Drink::Type::Chocolate:
      return new Chocolate();
      break;
  }
}
