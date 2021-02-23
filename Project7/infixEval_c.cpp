#include "infixEval_c.h"

    void Stack_c::resize(){
        char * arrR ;
        arrR = new char[size + 2];
        
        for(int i = 0; i < this->size; i++){
            arrR[i] = this->darr[i];
        }

        delete this->darr;

        this->darr = arrR;
        this->size += 2;
    }

    void Stack_c::init(){
        darr = new char [2];
        this->size = 2;
        this->inUse = 0;
    }


    Stack_c::Stack_c(){
        init();
    }

    boolean Stack_c::isEmpty(){
        if(inUse == 0){
            return True;
        }
        else{
            return False;
        }
    }
     void Stack_c::push(char x){
        this->inUse++;
        if(this->inUse == this->size){
            resize();
        }
        this->darr[this->inUse -1] = x;
    }

     char Stack_c::top(){
        if(isEmpty() == True){
            //std::cout << "no top, empty stack" << "\n" ;
            return '0';
        }
        return this->darr[this->inUse - 1];
    }

     void Stack_c::pop(){
         if(this->inUse == 0){
             //std::cout << "error, trying to pop empty stack"<< "\n" ;
             return;
         }
        this->inUse--;
    }

    void Stack_c::restore(){
        while(isEmpty() == False){
            pop();
        }
    }

    void Stack_c::display(){
        if(isEmpty() == True){
            //std::cout << "this stack is empty" << "\n" ;
            return;
        }
        for(int i = 0; i < this->inUse; i++){
            std::cout << " " << this->darr[i];
        }
    }

