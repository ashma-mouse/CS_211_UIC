// Project 7
// Started by Ashma Koirala on 01/12/2020
// CS 211
// University of Illinois Chicago

#include "proj7Tokens.h"
#include "infixEval_i.h"
#include "infixEval_c.h"
void printCommands();
int debugMode;
int eval(int v1, char op, int v2);
int popAndEval(Stack_i * values, Stack_c *operators);
void processExpression (Token inputToken, TokenReader *tr, Stack_i * values, Stack_c * operators);

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */

  for(int i = 0; i < argc; i++){
    if(!strcmp(argv[i],"-d")){
      debugMode = 1;
      break;
    }
    else{
      debugMode=0;
    }
  }

    Stack_i * values = new Stack_i();
    Stack_c * operators = new Stack_c();
    
    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");
  

    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr,values, operators);
      

       values->restore();
       operators->restore();
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression (Token inputToken, TokenReader *tr, Stack_i * values, Stack_c * operators)
{
 /**********************************************/
 /* Declare both stack head pointers here      */


 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
       if(debugMode == 1)
       printf ("Val: %d, ", inputToken.getValue() );

       // add code to perform this operation here
       values->push(inputToken.getValue());
       
      }

    /* The expression contains an OPERATOR */
    if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
        if(debugMode == 1)
       printf ("OP: %c, ", inputToken.getOperator() );

       // add code to perform this operation here
       

       if(inputToken.getOperator() == '(')
       {
       operators->push(inputToken.getOperator());
       }


      if( (inputToken.getOperator() == '+') ||
                 (inputToken.getOperator() == '-')){
          while((operators->isEmpty() == False) &&
                 ((operators->top() == '+') ||
                  (operators->top() == '-') ||
                  (operators->top() == '*') ||
                  (operators->top() == '/'))
                ){popAndEval(values, operators);}

            operators->push(inputToken.getOperator());
       }

       if( (inputToken.getOperator() == '*') ||
                 (inputToken.getOperator() == '/')){
                 while((operators->isEmpty() == False) &&
                  ((operators->top() == '*') ||
                  (operators->top() == '/'))
                  ){popAndEval(values, operators);}

            operators->push(inputToken.getOperator());
       }

       if(inputToken.getOperator() == ')')
       {
        while((operators->isEmpty() == False) &&
               (operators->top() != '(')){
          popAndEval(values, operators);
        }
        if((operators->isEmpty() == True)){
          std::cout << "theres been an error";
        }
        else{
          operators->pop();
        }
      // operators->push(inputToken.getOperator());
       }
      }

    /* get next token from input */
    inputToken = tr->getNextToken ();
   }

 /* The expression has reached its end */

 // add code to perform this operation here
   if(inputToken.equalsType(EOLN)){
    while((operators->isEmpty() == False))
    {
      popAndEval(values, operators);
    }
    std::cout <<"Expression result: \n" << values->top();
    values->pop();
    if(values->isEmpty() == False)
      std::cout << "\nerror, value stack is not empty";
      
   }
   
 printf ("\n");
}

int eval(int v1, char op, int v2){

  switch(op)
  {
    case '+':
      return (v1 + v2);
      break;
    case '-':
      return (v1 - v2);
      break;
    case '*':
      return (v1 * v2);
      break;
    case '/':
      return (v1/v2);
      break;
    default:
      std::cout << "hey... cant evaluate dis";
      return -999;
  }

}

int popAndEval(Stack_i * values, Stack_c *operators){
    int v1;
    int v2;
    int v3;
    char op;

    op = operators->top();
    operators->pop();
    v2 = values->top();
    values->pop();
    v1 = values->top();
    values->pop();
    v3 = eval ( v1, op, v2 );
    values->push(v3);
}

