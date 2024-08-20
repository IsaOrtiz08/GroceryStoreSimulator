#pragma once 
#include <iostream>
#include <fstream>
using namespace std;

struct listType {
    int cartId; //unique id assigned
    int itemCount; //amount of items generated
    int enterQTime; //current ‘time’ + shopping time
    int exitQTime; //enterQTime + checkout time
};

struct Node {
    listType data;
    Node* nextPtr;
};

class LinkedList {
public:
    LinkedList();
    void addElement(listType);
    listType peek();
    void delElement();
    void printList();
    bool listIsEmpty();
    static int listCount;

private:
    Node* headPtr;
};