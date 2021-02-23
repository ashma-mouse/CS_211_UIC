//Ashma Koirala
//CS 211- Project 1
//Professor Nashim Mobasheri
//Date: Sept 16, 2020

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//*Function 1- copying values from original array to another

void arrayCopy(int fromArray[], int toArray[], int size) {

    for (int i = 0; i < size; i++) {        //copy array

        toArray[i] = fromArray[i];
    }
}

//Function 2- sorting array in ascending order

void myFavoriteSort(int arr[], int size) {

    int tempArray;

    for (int i = 0; i < (size - 1); i++) {

        for (int j = 0; j < (size - i - 1); j++) {

            if (arr[j] > arr[j + 1]) {

                tempArray = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tempArray;
            }
        }
    }
}

//Funtion-3 Function of indexComparison
void indexComparison (int unsortedArr[], int sortedArr[], int size, int *counter) {
        counter = 0;
        for (int a = 0; a < size; a++) {
            if (unsortedArr[a] == sortedArr[a]) {
                counter++;
            }
        }
        if (counter > 0) {
            printf("%d values are in the same location in both arrays.\n", (int) counter/4);
        }

        else {
                printf("All elements change location in the sorted array.\n");
                
        }
  printf("Good bye");
    }

//Function-4 Function of targetSum
int targetSum (int arr[], int size, int target, int* index1, int* index2) {
    int initial = 0;
    int end = size - 1;
    while (initial != end) {
        if (arr[initial] + arr[end] == target) {
            *index1 = initial;
            *index2 = end;
            return 1;
        }
        if ((arr[initial] + arr[end]) < target) {
            initial++;
        }
        else {
            end--;
        }
    }
    return -1;
}

//main function
int main() {

    int *darr;
    int size = 5;
    darr = (int *)malloc(size * sizeof(int));
    int y;
    int target = 0;
    int index1;
    int index2;
    int counter = 0;
    int val = 0;

    printf("Enter in a list of numbers to be stored in a dynamic array.\n");
    printf("End the list with the terminal value of -999\n");
    //read in value and store it in val
    scanf("%d", &val);
    while (val != -999) {

        if (counter >= size) {
          //creating a temporary array
            int *tempArray;
            tempArray = (int *)malloc(size * 2 * sizeof(int)); //extending the size of array by multyplying the size
            for (int i = 0; i < size; i++) {
                tempArray[i] = darr[i];
            }
            free(darr); // deallocating the memory
            darr = tempArray;
            size = size*2;
        }

        darr[counter] = val;

        counter++;

        scanf("%d", &val);
    }

    size = counter;
    int toArray[size];
    arrayCopy(darr, toArray, counter);
    myFavoriteSort(toArray, counter);
        printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
        scanf("%d", &y);

        while (true) {
            if (y == 1) { // user input must be 1 for indexComparison
                indexComparison(darr, toArray, size, &counter);
                break;
            }
       else if (y == 2) { //user input must be 2 for targetSum
           printf("Enter in a list of numbers to use for searching.  \n");
           printf("End the list with a terminal value of -999\n");
           scanf("%d", &target); //getting target
           while (target!= -999) { //if the target is not -999
                if (targetSum(toArray, size, target, &index1, &index2) == 1) {
                    printf("Success! Elements at indices %d and %d add up to %d\n", index1, index2, target);
                }
                else {
                    printf("Target sum failed!\n");
                }
                scanf("%d", &target);
            }
           printf("Good bye");
           return 0; //if the target value is -999, the program ends with Good bye.
        }
       else {
          printf("Invalid input. Enter 1 or 2.\n"); //if user input is anything else than 2 or 1
          scanf("%d", &y);
        }
        }
        return 0;
}
