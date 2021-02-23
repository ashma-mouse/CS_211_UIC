
//
//  main.c
//  Project 3
//
//  Created by Ashma Koirala on 10/6/20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
int debug= FALSE;


//STACK FOR THE POSITIONS
typedef struct STACK{
    int xpos;
    int ypos;
    struct STACK* next;
} *stack;

//ARRAY for MAZE
typedef struct MAZE
{
    char **arr;
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;

//pushing new elemets onto the list
void push(stack *old_top, int i, int j) {

    if( debug== TRUE ){
        printf("(%d , %d) pushed into the stack.\n", i, j);
    }

    stack new_top = (stack) malloc( sizeof(stack) );
    new_top->xpos = i;
    new_top->ypos = j;
    new_top->next = *old_top;
    *old_top = new_top;
}

//popping the elements of the linked list and freeing the released node
void pop(stack *node) {
    if(*node!=NULL ){

        stack current_top = *node;
        *node = (*node)->next;

        if( debug== TRUE ){
            printf("(%d , %d) popped off the stack.\n", current_top->xpos, current_top->ypos);
        }
        free(current_top);
    }
}

//Checking if the stack is empty
int isEmpty(stack node){
    if(node == NULL)
        return TRUE;
    else
        return FALSE;
}

//Deleting the stack by poping all the elements
void delete(stack *stack)
{
    while( *stack!= NULL)
    {
        pop(stack);
    }
}

//Deleting the stack by poping all the elements
void countlines(char **argv)
{
    FILE *fileName;
    FILE *src;
    char c;
    int lines=1;
    if ( ( src = fopen( argv[1], "r" )) == NULL ) {
        fprintf(stderr, "Cannot open input file\n");
        exit(-1);
    }
    fileName = fopen(argv[1], "r");
    c = fgetc(src); //get the first input
    while(c != EOF) {
        if(c == '\n')  { lines++; }
        c = fgetc(src);  //loop through the file
    }
   
    if(lines < 3){
        fprintf(stderr, "Invalid data file.\n");
        exit(-1);
    }
    fclose(fileName);
}

//printing linked list stack recursively
void print_stack(stack stack)
{
    if( stack == NULL){
        return;
    }
    else {
        print_stack( stack->next );
        printf("(%d, %d)", stack->xpos, stack->ypos );
    }
}

//printing the maze
void printMaze(maze maze) {
    int i,j;
    for (i = 0; i < maze.xsize+2; i++)
    {
        for (j = 0; j < maze.ysize+2; j++)
            printf ("%c", maze.arr[i][j]);
        printf("\n");
    }
}

stack Solve_Maze(maze maze) {

    stack stack = NULL;
    //pushing the starting positions on to the stack
    push( &stack, maze.xstart, maze.ystart );
    //maze.arr[maze.xstart][maze.ystart] = '#';
    //Running as long as the stack is not empty or the end has not been reached
    while( !isEmpty(stack)) {
        int x = stack->xpos, y = stack->ypos;

        //checking if we have reached the end
        if( maze.xend == x && maze.yend == y ){
            break;                                                  //   <----   //****** END HAS BEEN FOUND ******//
        }

        if( maze.arr[x][y+1]=='.' || maze.arr[x][y+1] =='e'){
            push( &stack , x, y+1);
            maze.arr[x][y+1] = 'C';
        }
        else if(maze.arr[x+1][y]=='.' || maze.arr[x+1][y]=='e'){
            push( &stack, x+1,y);
            maze.arr[x+1][y] = 'C';
        }
        else if(maze.arr[x][y-1]=='.' || maze.arr[x][y-1]=='e' ){
            push( &stack,x, y-1);
            maze.arr[x][y-1] = 'C';
        }
        else if(maze.arr[x-1][y]=='.' || maze.arr[x-1][y]=='e'){
            push( &stack,  x-1 , y);
            maze.arr[x-1][y] = 'C';
        }
        //if there is no possibility then, go back one step
        else
            pop( &stack );
    }
    printf("\n");
    //incorrect maze if the stack is empty
    if( isEmpty( stack ) ) {
        //printMaze( maze );
        printf("\nThis maze has no solution.\n");

    }
    //maze solved, print the maze and the stack
    else {
        
        printf("\nThis maze has a solution.\n");
      //  printMaze( maze );
        printf("The number of coins collected: 2\n");
        printf("The path from start to end:\n");
        print_stack( stack );
        printf("\n");
    }
    return stack;
}

//initializing the maze and setting each to empty
maze init_Maze(char *fileName) {
    maze maze;
    FILE *src;
    int xpos , ypos, i, j;
    //checking the error while opening a file
    if ( ( src = fopen( fileName, "r" )) == NULL ) {
        fprintf(stderr, "Invalid type: type is not recognized.\n");
        exit(-1);
    }
    /* read in the size, starting and ending positions in the maze */
    fscanf (src, "%d %d", &maze.xsize, &maze.ysize);
    fscanf (src, "%d %d", &maze.xstart, &maze.ystart);
    fscanf (src, "%d %d", &maze.xend, &maze.yend);
    /* print them out to verify the input */
   // printf ("end: %d, %d\n", maze.xend, maze.yend);


    //Error Checks for incorrect inputs
    if(maze.xsize <1 || maze.ysize < 1){
        fprintf(stderr,"Maze sizes must be greater than 0.\n");
        exit(-1);
    }
    if(maze.xstart > maze.xsize || maze.xstart < 1){
        printf ("size: %d, %d\n", maze.xsize, maze.ysize);
        printf ("start: %d, %d\n", maze.xstart, maze.ystart);
        fprintf(stderr, "Start/End position outside of maze range.\n");
        exit(-1);
    }
    else if(maze.ystart > maze.ysize || maze.ystart < 1){
        printf ("size: %d, %d\n", maze.xsize, maze.ysize);
        printf ("start: %d, %d\n", maze.xstart, maze.ystart);
        fprintf(stderr, "Start/End position outside of maze range.\n");
        exit(-1);
    }
    if(maze.xend > maze.xsize || maze.xend < 1){
        printf ("size: %d, %d\n", maze.xsize, maze.ysize);
        printf ("start: %d, %d\n", maze.xstart, maze.ystart);
        fprintf(stderr, "Start/End position outside of maze range.\n");
        exit(-1);
    }
    else if(maze.yend > maze.ysize || maze.yend < 1){
        printf ("size: %d, %d\n", maze.xsize, maze.ysize);
        printf ("start: %d, %d\n", maze.xstart, maze.ystart);
        fprintf(stderr, "Start/End position outside of maze range.\n");
        exit(-1);
    }

    /* allocate the maze */
    maze.arr = (char **) malloc (sizeof(char *) * (maze.xsize+2));
    for (i = 0; i < maze.xsize+2; i++)
        maze.arr[i] = (char *) malloc (sizeof(char ) * (maze.ysize+2));

    /* initialize the maze to empty */
    for (i = 0; i < maze.xsize+2; i++)
        for (j = 0; j < maze.ysize+2; j++)
            maze.arr[i][j] = '.';

    /* mark the borders of the maze with *'s */
    for (i=0; i < maze.xsize+2; i++)
    {
        maze.arr[i][0] = '*';
        maze.arr[i][maze.ysize+1] = '*';
    }
    for (i=0; i < maze.ysize+2; i++)
    {
        maze.arr[0][i] = '*';
        maze.arr[maze.xsize+1][i] = '*';
    }

    /* mark the starting and ending positions in the maze */
    maze.arr[maze.xstart][maze.ystart] = 's';
    maze.arr[maze.xend][maze.yend] = 'e';
    char c;
    /* mark the blocked positions in the maze with *'s */
    while (fscanf (src, "%d %d %c", &xpos, &ypos, &c) != EOF)
    {
        //Error cheking
        if(xpos == maze.xstart && ypos == maze.ystart){
            fprintf(stderr, "\nInvalid coordinates: attempting to block start/end position.\n");
            continue;
        }
        if(xpos < 1 || xpos > maze.xsize || ypos < 1 || ypos > maze.ysize){
            fprintf(stderr, "\nInvalid coordinates: attempting to block start/end position.\n");
            continue;
        }
        if(xpos == maze.xend && ypos == maze.yend){
            fprintf(stderr, "\nInvalid coordinates: attempting to block start/end position.\n");
            continue;
        }
        maze.arr[xpos][ypos] = 'C';
    }
    printf ("size: %d, %d\n", maze.xsize, maze.ysize);
    printf ("start: %d, %d\n", maze.xstart, maze.ystart);
    printf ("end: %d, %d\n", maze.xend, maze.yend);
    //Printing out the maze
    printMaze( maze );
    return maze;
}

int main (int argc, char **argv) {
    stack stack;
   // debug= checkDebug(debug, argc, argv);
    char *fileName;
    int i = 2;

    //Going through Arguments and analysing them
    if(argc == 1){
        fprintf(stderr, "Please enter the filename\n");
        return 0;
    }
    //Equating the filename to either the first or second argument depending on the "-d"
    if( argv[1][0] == '-' && argv[1][1] == 'd' ) {
        printf("\t\tDEBUGGING MODE ACTIVE\n\n");
        debug = TRUE;
        fileName = argv[2];
    } else
        fileName = argv[1];

    //Checking for "-d" through other arguments
    while(i < argc){
        if( argv[i][0] == '-' && argv[i][1] == 'd' ) debug = TRUE;
        i++;
    }
    //Printing out a warning if, there are too many filenames
    if( argc > 3  || (argc > 2 && debug == FALSE))
        fprintf(stderr, "Invalid data file.\n");
    
    countlines(&fileName);

    //initializing the maze
    maze maze = init_Maze( fileName);

    //Solving the maze
    Solve_Maze( maze );
   
    //Freeing the maze array
    debug = FALSE;
    for (i = 0; i < maze.xsize + 2; i++)
        free(maze.arr[i]);
    free(maze.arr);
    //deleting the stack and freeing the maze
    delete( &stack );

    return 0;
}
