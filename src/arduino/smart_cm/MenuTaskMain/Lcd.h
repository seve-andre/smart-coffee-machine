#ifndef __LCD__
#define __LCD__

#include <LiquidCrystal_I2C.h>

class Lcd {
  public:
    static Lcd* getInstance();
    void print(char message[]);
    void printAt(int n_col, int n_row, char message[]);

  private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
    Lcd();
    static Lcd* instance;
    void printNewMessageAt(int n_col, int n_row, char message[]); 
};

#endif
