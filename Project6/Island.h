
// This is header file for Node, MyList, NodeFileName, ListFileName, Island

#ifndef ISLAND_H
#define ISLAND_H

#include "MyList.h"

//Island
class Island
{
private:
    bool visited;
    MyList front;
    int previousLocation;

public:
    Island();
    ~Island();

    void AddEdge(int v1);
    bool EdgeExists(int v1);
    void RemoveEdge(int v1);
    void Visited();
    void Unvisited();
    bool isVisited();
    void Show();
    bool Connected();
    Node* Head();
    void setPreviousLocation(int v1);
    int getPreviousLocation();
};

#endif // ISLAND_H


