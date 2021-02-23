//CS 211 - Project 2
//Ashma Koirala

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// C boolean set-up
#define TRUE 1
#define FALSE 0
int DebugMode;

typedef struct StackStruct
{
    char    *darr;  // pointer to dynamic array that holds the stack
    int     size;  // current size of the dynamic array
    int     counter; // top of stack
           
} Stack;

void init (Stack *s)
{
    s->size = 4;
    s->darr = (char*) malloc ( sizeof (char) * s->size );
    s->counter  = 0;

}

void push (Stack* s, int val) {
    if (s->counter + 1 >= s->size) {
        char *darr2;
        int oldSize = s->size;
        int numElements = 0;
        darr2 = s->darr;
        s->darr = (char*)malloc (sizeof(char) *(s->size + 4));
        if (DebugMode == TRUE) {
            numElements++;
            printf ("The stack has grown from %d to %d, and a total of %d values were copied into the larger array.\n", oldSize, s->size, numElements);
        }
        for (int i = 0; i < s->size; i++) {
            
            s->darr[i] = darr2[i];
        }
        free(darr2);
        s->size = s->size + 4;
    }

    s->darr[s->counter] = val; // adding value to the top
    s->counter  = s->counter + 1;
}

bool isEmpty (Stack *s)
{
    if ( s->counter == 0)
        return true;
    else
        return false;
}

char top (Stack *s)
{
    return (  s->darr[s->counter-1] );
}

 
void pop (Stack* s)
{
    s->counter = s->counter - 1;
}

void reset (Stack *s)
{
    while (!isEmpty(s)) {
        pop(s);
    }
}

int counter (Stack* s) {
    return s-> counter;
}

int getIndex (char L2[], char text) {
    for (int i = 0; i < sizeof(L2); i++) {
        if (L2[i] == text) {
            return i;
        }
    }
    return 0;
}

void deAllocate (Stack *s) {
    free(s->darr);
}

int main(int argc, char const *argv[])
{
    DebugMode = FALSE;
    int i;
    for (i=0; i < argc; i++){
        if(strcmp(argv[i], "-d")== 0) {
            DebugMode = TRUE;
        }
    }
    char L[] = "abcd";
    char L2[] = "mnop";

    char text;
    char *letterList[15];
    char *validletterList[15];
    Stack stacky;
    init(&stacky);
    int validletterSize = 0;

    char input[300];

    for (int i = 0; i < 15; i++) {
        letterList[i] = (char*) malloc (sizeof (char) * 15);
    }

    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf ("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);

        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
            break;

        printf ("%s\n", input);
        /*Start tokenizing the input into words separated by space
         We use strtok() function from string.h*/
        /*The tokenized words are added to an array of words*/

        char delim[] = " ";
        char *ptr = strtok(input, delim);
        int j = 0 ;

        while (ptr != NULL)
        {
            strcpy(letterList[j], ptr);
            ptr = strtok(NULL, delim);
            j++;

        }

        validletterSize = 0;

        /*Run the algorithm to decode the message*/

        for (int i = 0; i < j; i++) {
            reset(&stacky);
            long letterSize = strlen(letterList[i]);
            letterList[i][letterSize] = '\0';
            bool verify = true;

            for (int k = 0; k < letterSize; k++) {
               
                text = tolower(letterList[i][k]);
                if (text == 'a' || text == 'b' || text == 'c' || text == 'd') {
                    if (DebugMode == TRUE) {
                printf("Character %c was pushed into the stack.\n", text);
                        printf("No valid word decoded.\n");
                    }
                    push(&stacky, text);
                }

                if (text == 'm' || text == 'n' || text == 'o' || text == 'p') {
                    if (isEmpty(&stacky)) {
                        verify = false;
                        break;
                    }

                    if (L[getIndex(L2, text)] == top(&stacky)) {
                        if (DebugMode == TRUE) {
                        printf("Character %c was popped from the stack.\n", top(&stacky));
                        }
                        pop(&stacky);
                        verify = isEmpty(&stacky);
                    }

                    else {
                        verify = false;
                        break;
                    }

                }
            }

            if (!isEmpty(&stacky)) {
                verify = false;
            }

            if (verify == true) {
                validletterList[validletterSize] = letterList[i];
                validletterSize++;
            }

            reset(&stacky);
        }

        if (validletterSize == 0) {
            printf("No valid word decoded.");
        }

        for (int a = 0; a < validletterSize; a++) {
            for (int k = 0; k < strlen(validletterList[a]); k++) {
                validletterList[a][k] = tolower(validletterList[a][k]);
                if (validletterList[a][k] == 'a' || validletterList[a][k] == 'b' || validletterList[a][k] == 'c' || validletterList[a][k] == 'd') {
                    printf("%c", validletterList[a][k]);
                }
            }
            
            printf(" ");

        }
        printf("\n");


    }
    deAllocate(&stacky);
    printf ("\nGoodbye\n");
    return 0;
}

