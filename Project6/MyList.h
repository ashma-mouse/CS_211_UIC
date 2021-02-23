
#ifndef MYLIST_H
#define MYLIST_H


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>

// Node
class Node
{
private:
    int elem;
    Node* next;

public:
    Node (int v1);
    Node (int v1, Node* n);

    void setElem (int e);
    int getElem ();
    void setNext (Node* n);
    Node* getNext();
};

//MyList
class MyList
{
private:
    Node* head;

public:
    MyList();
    ~MyList();

    void show();
    void addToFrontOfList(int v1);
    void addToBackOfList(int v1);
    int getValueAtFrontOfList();
    void removeValueFromFrontOfList();
    void remove(int v1);
    void removeAll();
    bool isEmpty();
    int search(int v1);
    Node* Head();
};

//NodeFileName
class NodeFileName
{
private:
    char* name;
    NodeFileName* next;

public:
    NodeFileName (char* fileName);
    void setNext(NodeFileName* n);
    NodeFileName* getNext();
    char* Name();
};

//ListFileName
class ListFileName
{
private:
    NodeFileName* head;

public:
    ListFileName();
    ~ListFileName();

    bool OpenFile(char* fileName);
    void Name(char* fileName);
    void removeAll();
    void FileRemove(char* fileName);
};

#endif // MYLIST_H


