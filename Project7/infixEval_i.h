#ifndef INFIXEVALI_H
#define INFIXEVALI_H
#include <iostream>
typedef enum  {False = 0, True,} boolean;



class Stack_i{
    
private:
    int * darr;
    int size;
    int inUse;
    void resize();
protected:
    void init();
public:
    Stack_i();
    boolean isEmpty();
    void push(int x);
    int top();
    void pop();
    void restore();
    void display();
};
#endif 
