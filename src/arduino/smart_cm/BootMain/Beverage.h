#ifndef __BEVERAGE__
#define __BEVERAGE__

class Beverage {
  public:
    Beverage();
    Beverage(unsigned int n_coffee, unsigned int n_thea, unsigned int n_chocolate);
    void takeACoffee();
    void takeAThea();
    void takeAChocolate();
    
    void printCoffeeMessage();
    void printTheaMessage();
    void printChocolateMessage();
    
    unsigned int getNCoffee();
    unsigned int getNThea();
    unsigned int getNChocolate();

  private:
    unsigned int n_coffee;
    unsigned int n_thea;
    unsigned int n_chocolate;
};

#endif
