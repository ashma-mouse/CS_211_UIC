#include "infixEval_i.h"

    void Stack_i::resize(){
        int * arrR ;
        arrR = new int[size + 2];
        
        for(int i = 0; i < this->size; i++){
            arrR[i] = this->darr[i];
        }

        delete this->darr;

        this->darr = arrR;
        this->size += 2;
    }

    void Stack_i::init(){
        darr = new int [2];
        this->size = 2;
        this->inUse = 0;
    }


    Stack_i::Stack_i(){
        init();
    }

    boolean Stack_i::isEmpty(){
        if(inUse == 0){
            return True;
        }
        else{
            return False;
        }
    }
     void Stack_i::push(int x){
        this->inUse++;
        if(this->inUse == this->size){
            resize();
        }
        this->darr[this->inUse -1] = x;
    }

     int Stack_i::top(){
        if(isEmpty() == True){
            std::cout <<"\n" << "no top, empty stack"<< "\n" ;
            return -999;
        }
        return this->darr[this->inUse - 1];
    }

     void Stack_i::pop(){
        if(this->inUse == 0){
             //std::cout << "error, trying to pop empty stack"<< "\n" ;
             return;
         }
        this->inUse--;
    }

    void Stack_i::restore(){
        while(isEmpty() == False){
            pop();
        }
    }

    void Stack_i::display(){
        if(isEmpty() == True){
            //std::cout << "this stack is empty"<< "\n" ;
            return;
        }
        for(int i = 0; i < this->inUse; i++){
            std::cout << " " << this->darr[i];
        }
    }


