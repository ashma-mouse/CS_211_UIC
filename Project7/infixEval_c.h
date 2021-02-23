#ifndef INFIXEVALC_H
#define INFIXEVALC_H
#include <iostream>
#include "infixEval_i.h"
//extern typedef enum  {False = 0, True,} boolean;

class Stack_c{
    
private:
    char * darr;
    int size;
    int inUse;
    void resize();
protected:
    void init();
public:
    Stack_c();
    boolean isEmpty();
    void push(char x);
    char top();
    void pop();
    void restore();
    void display();
};
#endif 
