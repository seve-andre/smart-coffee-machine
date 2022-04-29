#ifndef __DRINK__
#define __DRINK__

class Drink {
  public:
    enum Type {
      Tea,
      Coffee,
      Chocolate
    };
    virtual void printDrink() = 0;

  protected:
    void printMessage(char msg) {
        //lcd.print("making a " + msg + "...");
    };

    private:
      unsigned int quantity;
};

#endif
