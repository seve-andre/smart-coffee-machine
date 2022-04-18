#ifndef __INDENT__
#define __INDENT__

class Indent {
  public:
    Indent();
    void moveNext();
    void movePrev();
    int getPositionIndent();
    
    const unsigned int maxRow = 2;
    unsigned int positionIndent;
};


#endif
