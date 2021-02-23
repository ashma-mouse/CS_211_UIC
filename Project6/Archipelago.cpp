// This file contains the main() and ArchipelagoExpedition class
// This program is implementing the classes and using Breadth first search so we can get
// the shortest path between islands and insert and implement the islands

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdbool>
#include "Island.h"

class ArchipelagoExpedition
{
private:
    // Create the Data Members for the Archipelago Network here
    int allocated;
    ListFileName *fileName;
    Island *islands;

public:

    // Use a constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition()
    {
        allocated = 10;
        fileName = new ListFileName();
        islands = new Island[allocated+1];
    }

    ~ArchipelagoExpedition()
    {
        delete[] islands;
    }

    // The main loop for reading in input
    void processCommandLoop (FILE* inFile)
    {
        char  buffer[300];
        char* input;

        input = fgets ( buffer, 300, inFile );   // get a line of input

        // loop until all lines are read from the input
        while (input != NULL)
        {
            // process each line of input using the strtok functions
       
            char* command;
            command = strtok (input , " \r\n\t");
            printf ("*%s*\n", command);

            if ( command == NULL )
                printf ("Blank Line\n");

            else if ( strcmp (command, "q") == 0)
                exit(1);

            else if ( strcmp (command, "?") == 0)
                showCommands();

            else if ( strcmp (command, "t") == 0)
                doShortestPath();

            else if ( strcmp (command, "r") == 0)
                doResize();

            else if ( strcmp (command, "i") == 0)
                doInsert();

            else if ( strcmp (command, "d") == 0)
                doDelete();

            else if ( strcmp (command, "l") == 0)
                doList();

            else if ( strcmp (command, "f") == 0)
                doFile();

            else if ( strcmp (command, "#") == 0)
                ;
            else
                printf ("Command is not known: %s\n", command);
            input = fgets ( buffer, 300, inFile );   // get the next line of input

        }
    }

    void showCommands()
    {
        printf ("The commands for this project are:\n");
        printf ("  q \n");
        printf ("  ? \n");
        printf ("  # \n");
        
        printf ("  t <int1> <int2> \n");
        printf ("  r <int> \n");
        printf ("  i <int1> <int2> \n");
        printf ("  d <int1> <int2> \n");
        printf ("  l \n");
        printf ("  f <filename> \n");
    }

    // this function actually marks the elements as visited
    bool bfs(int b, MyList *IslandQueue)
    {
        // loop until IslandQueue is empty
        while(!IslandQueue->isEmpty())
        {
            // set the element at front of IslandQueue to a
            int a = IslandQueue->getValueAtFrontOfList();
            // remove the element at front of IslandQueue
            IslandQueue->removeValueFromFrontOfList();

            Node* tmp = islands[a].Head();

            // for loop for going until c can reach one ferry ride
            for(; tmp != NULL; tmp = tmp->getNext())
            {
                // if element is not visited then set it to visited and insert it in IslandQueue
                if (!islands[tmp->getElem()].isVisited() && islands[tmp->getElem()].getPreviousLocation() == -1)
                {
                    islands[tmp->getElem()].Visited();
                    islands[tmp->getElem()].setPreviousLocation(a);
                    if (tmp->getElem() == b)
                        return true;
                    IslandQueue->addToBackOfList(tmp->getElem());
                }//if (!islands[tmp
            }//for(; tmp !
        }//while(!IslandQueue
        return false;
    }//bool bfs

    // this function returns the list of elements that can be reached in one ferry ride
    MyList* breadthFirstSearch(int x, int y)
    {
        // for loop for marking every element as not visited and setting the previous location to -1
        for(int i=0; i<allocated+1; i++)
        {
            islands[i].Unvisited();
            islands[i].setPreviousLocation(-1);
        }

        MyList *IslandQueue = new MyList;
        IslandQueue->addToBackOfList(x);

        // if helper function return false then return empty IslandQueue
        if(!bfs(y, IslandQueue))
        {
            printf("You can NOT get from island %d to island %d in one or more ferry rides\n", x, y);
            IslandQueue->removeAll();
            return IslandQueue;
        } else
        {
            printf("You can get from island %d to island %d in one or more ferry rides", x, y);
            MyList *pathList = new MyList;
            int currentIsland = y;
         pathList->addToFrontOfList(y);
            // insert the elements in pathList and then return it
            do
            {
                currentIsland = islands[currentIsland].getPreviousLocation();
                pathList->addToFrontOfList(currentIsland);
            }while(currentIsland != x);

            return pathList;
        }//else
    }// MyList* breadthFirstSearch

    // this function finds the shortest path
    void doShortestPath ( )
    {
        int val1 = 0;
        int val2 = 0;
        MyList *showingthepath;

        // get an integer value from the input
        char* next = strtok (NULL, " \n\t");
        //printf("%s\n", next);
        if (next == NULL)
        {
            printf ("Integer value expected\n");
            return;
        }

        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \n\t");

        //printf("%s\n", next);
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        printf ("Performing the Travel Command from %d to %d\n",
                val1, val2);

        // display the path
        showingthepath = breadthFirstSearch(val1, val2);
        if(!showingthepath->isEmpty()) {
           // printf("\nList Path: ");
            //showingthepath->show();
            printf("\n");
        }
    }

    // resizes the array to contain certain number of elements
    void doResize()
    {
        int val1 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \n\t");
        //printf("%s\n", next);

        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        if (val1 <= 0) {
            printf("Error message: Can't assign size less or equal to zero.\n");
            return;
        }

        // erases everything, prepare for next Island[size]
        // ...
        this->~ArchipelagoExpedition();

        this->allocated = val1;
        islands = new Island[this->allocated+1];

        printf ("Performing the Resize Command with %d\n", val1 );
    }//void doResize()

    // inserts the element
    void doInsert()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \n\t");
      //  printf("%s\n", next);
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \n\t");

       // printf("%s\n", next);
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }
        // check if these conditions satisfies first
        // ...
        if((val1 <= 0 || val1 > this->allocated) || (val2 <= 0 || val2 > this->allocated)) {
            printf("Invalid value for island\n");
            return;
        }
        
        islands[val1].AddEdge(val2);
        printf("Performing the Insert Command for %d\n", val1);
        
        if(islands[val1].EdgeExists(val2)) {
            printf("Ferry ride already added!\n");
            return;
        }
        // insert
       // islands[val1].AddEdge(val2);
        //printf("Performing the Insert Command for %d\n", val1);
    }//void doInsert()

    // deletes the element
    void doDelete()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok (NULL, " \n\t");
       // printf("%s\n", next);
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val1 = atoi ( next );
        if ( val1 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok (NULL, " \n\t");

        //printf("%s\n", next);
        if ( next == NULL )
        {
            printf ("Integer value expected\n");
            return;
        }
        val2 = atoi ( next );
        if ( val2 == 0 && strcmp (next, "0") != 0)
        {
            printf ("Integer value expected\n");
            return;
        }

        // check if these conditions satisfies first
        // ...
        if((val1 <= 0 || val1 > this->allocated) || (val2 <= 0 || val2 > this->allocated)) {
            printf("Invalid value for island\n");
            return;
        }

        if(!islands[val1].EdgeExists(val2)) {
            printf("Error message: Can't delete not in the list.\n");
            return;
        }
        // delete
        islands[val1].RemoveEdge(val2);
        printf("Performing the Delete Command for %d\n", val1);

    }//void doDelete()

    // print the whole list
    void doList()
    {
        printf("Displaying the adjacency list:\n");

        for(int i = 1; i < this->allocated+1; i++){
            printf("#%d",i);
            if(islands[i].Connected() == true) {
                printf("-->");
            }
            else {
                printf("  -->  ");
                islands[i].Show();
            }
            printf("\n");
        }
    }//void doList()

    // f command
    void doFile()
    {
        // get a filename from the input
        char* fname = strtok (NULL, " \r\n\t");
        if ( fname == NULL )
        {
            printf ("Filename expected\n");
            return;
        }

        printf ("Performing the File command with file: %s\n", fname);

        // next steps:  (if any step fails: print an error message and return )
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns

        // next steps:  (if any step fails: print an error message and return )
        //  1. verify the file name is not currently in use
        if(fileName->OpenFile(fname)) {
            printf("File is already in use\n");
            return;
        }

        //  2. open the file using fopen creating a new instance of FILE*
        FILE* infile;
        infile = fopen(fname, "r");

        if(infile == NULL) {
            printf("Error message: FILE doesn't exist.\n");
            return;
        }

        fileName->Name(fname);

        processCommandLoop(infile);

        fclose(infile);
        fileName->FileRemove(fname);
    }//void doFile()
};

int main (int argc, char** argv)
{
    // set up the variable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf ("\nEnter commands at blank line\n");
    printf ("    (No prompts are given because of f command)\n");
   islandData.processCommandLoop (inFile);

    printf ("Goodbye\n");
    return 1;
}
