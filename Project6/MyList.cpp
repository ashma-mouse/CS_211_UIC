
#include "MyList.h"

Node::Node(int v1)
{
    elem = v1;
    next = NULL;
}

Node::Node(int v1, Node* n)
{
    elem = v1;
    next = n;
}

void Node::setElem(int e)
{
    elem = e;
}

int Node::getElem()
{
    return elem;
}

void Node::setNext(Node* n)
{
    next = n;
}

Node* Node::getNext()
{
    return next;
}

MyList::MyList()
{
    head = NULL;
}
// deconstructor
MyList::~MyList()
{
    // doing a show() so we can see when the destructor is called
   // printf ("In Destructor: ");
    show();

    // Note that removeAll() does same operation as required by destructor
    removeAll();
}
// display the list
void MyList::show()
{
    Node *tmp = head;
    while(tmp != NULL) {
        printf( "%d  ", tmp->getElem());
        tmp = tmp->getNext();
    }
}
// checks if its empty
bool MyList::isEmpty()
{
    if(head == NULL)
        return true;

    return false;
}

void MyList::addToFrontOfList(int v1)
{
    Node* tmp = new Node(v1);

    tmp->setNext(head);
    head = tmp;
}

// insert
void MyList::addToBackOfList(int v1)
{
    Node* tmp = new Node(v1);

    Node *curr = head;
    Node *prev = NULL;

    while((curr != NULL) && (curr->getElem() < v1))
    {
        prev = curr;
        curr = curr->getNext();
    }

    tmp->setNext(curr);

    if(prev == NULL) {
        head = tmp;
    }
    else {
        prev->setNext(tmp);
    }
}

void MyList::removeValueFromFrontOfList()
{
    if(head != NULL)
        head = head->getNext();
}

// remove from the list
void MyList::remove (int v1)
{
    Node* curr = head;
    Node* prev = NULL;

    while ( (curr != NULL) && (curr->getElem() != v1) )
    {
        prev = curr;
        curr = curr->getNext();
    }

    if(curr == NULL)
        return;

    if(prev == NULL)
    {
        head = curr->getNext();
        delete curr;
    }
    else
    {
        prev->setNext(curr->getNext());
        delete curr;
    }
}

int MyList::getValueAtFrontOfList()
{
    return head->getElem();
}

// removes all list
void MyList::removeAll()
{
    Node* tmp = head;
    Node* tmp2 = NULL;

    while(tmp != NULL) {
        tmp2 = tmp;
        tmp = tmp->getNext();
        delete tmp;
    }
    head = NULL;
}

// search and if find returns 1
int MyList::search(int v1)
{
    if(head == NULL)
        return 0;

    Node* tmp = head;

    while(tmp != NULL)
    {
        if(tmp->getElem() == v1)
            return 1;

        tmp = tmp->getNext();
    }
    return 0;
}

Node* MyList::Head()
{
    if(head == NULL)
        return NULL;

    return head;
}

// This is the class NodeFileName
//_________________________________________________________________________________________________

//constructor
NodeFileName::NodeFileName (char* fileName)
{
    name = fileName;
    next = NULL;
}

// get file name
char* NodeFileName::Name()
{
    return name;
}

// set next
void NodeFileName::setNext (NodeFileName* n)
{
    next = n;
}

// get next
NodeFileName* NodeFileName::getNext()
{
    return next;
}

// This is the class ListFileName
//_________________________________________________________________________________________________

// constructor
ListFileName::ListFileName()
{
    head = NULL;
}

// deconstructor
ListFileName::~ListFileName()
{
    removeAll();
}

void ListFileName::removeAll()
{
    NodeFileName* tmp = head;
    NodeFileName* next = NULL;

    while(tmp != NULL) {
        next = tmp->getNext();
        delete tmp;
        tmp = next;
    }
    head = NULL;
}

// add file name
void ListFileName::Name(char* fileName)
{
    NodeFileName* tmp = new NodeFileName(fileName);

    NodeFileName *curr = head;
    if (curr == NULL) {
        head = tmp;
        return;
    }
    while(curr->getNext() != NULL)
        curr = curr->getNext();

    curr->setNext(tmp);
}

// check if its open
bool ListFileName::OpenFile(char *fileName)
{
    NodeFileName *tmp = head;

    while(tmp != NULL) {
        if (!strcmp(tmp->Name(), fileName))
            return true;

        tmp = tmp->getNext();
    }
    return false;
}

// remove file node
void ListFileName::FileRemove(char *fileName)
{
    NodeFileName* curr = head;
    NodeFileName* prev = NULL;

    while ((curr != NULL) && (curr->Name() != fileName))
    {
        prev = curr;
        curr = curr->getNext();
    }

    if(curr == NULL)
        return;

    if(prev == NULL) {
        head = curr->getNext();
        delete curr;
    }
    else {
        prev->setNext(curr->getNext());
        delete curr;
    }
}


