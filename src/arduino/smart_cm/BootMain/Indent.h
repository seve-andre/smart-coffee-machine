#ifndef __INDENT__
#define __INDENT__

class Indent {
  public:
    Indent();
    void moveUp();
    void moveDown();
    int getPositionIndent();
    
    const unsigned int maxRow = 2;
    unsigned int positionIndent;
};


#endif
