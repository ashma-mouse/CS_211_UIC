
// This is source code file for Island

#include "Island.h"

Island::Island()
{
    visited = false;
}

Island::~Island()
{
    front.removeAll();
}

void Island::AddEdge(int v1)
{
    front.addToBackOfList(v1);
}

bool Island::EdgeExists(int v1)
{
    if(front.search(v1) == 1) {
        return true;
    }
    return false;
}

void Island::RemoveEdge(int v1)
{
    front.remove(v1);
}

void Island::Show()
{
    front.show();
}

bool Island::Connected()
{
    if(front.isEmpty())
        return true;

    return false;
}

void Island::Visited()
{
    this->visited = true;
}

void Island::Unvisited()
{
    this->visited = false;
}

Node* Island::Head()
{
    return front.Head();
}

bool Island::isVisited()
{
    return this->visited;
}

void Island::setPreviousLocation(int v1)
{
    previousLocation = v1;
}

int Island::getPreviousLocation()
{
    return previousLocation;
}



