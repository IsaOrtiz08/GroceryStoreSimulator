#include <iostream>
#include "LinkedList.h"

using namespace std;
int LinkedList::listCount = 0;
// default constructor
LinkedList::LinkedList() {
    headPtr = nullptr;
}
//adds a new element to the list
void LinkedList::addElement(listType element) {
    Node* newNode = new Node;
    newNode->data = element;
    newNode->nextPtr = nullptr;
  // sets headPtr if list is empty
    if (headPtr == nullptr) {
        headPtr = newNode;
    }
      // otherwise adds a node to the end of the list
    else {
        Node* currNode = headPtr;
        Node* prevNode = nullptr;

        while (currNode != nullptr && currNode->data.enterQTime < element.enterQTime) {
            prevNode = currNode;
            currNode = currNode->nextPtr;
        }
        if (prevNode == nullptr) {
            headPtr = newNode;
        }
        else {
            prevNode->nextPtr = newNode;
        }
        newNode->nextPtr = currNode;
    }
    listCount++;
}
// reveal the headPtrs data
listType LinkedList::peek() {
    return headPtr->data;
}
// remove data (always from headPtr)
void LinkedList::delElement() {
    if (headPtr != nullptr) {
        Node* tempNode = headPtr;
        headPtr = headPtr->nextPtr;
        delete tempNode;

        listCount--;
    }
}
//output individual items in list
void LinkedList::printList() {
    if (headPtr == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* currNode = headPtr;
    while (currNode != nullptr) {
        cout << "Cart ID: " << currNode->data.cartId
                  << " | Item count: " << currNode->data.itemCount
                  << " | Enter Q Time: " << currNode->data.enterQTime
                  << " | Exit Q Time: " << currNode->data.exitQTime
                  <<endl <<endl;
        currNode = currNode->nextPtr;
    }
}
// returns true if list is empty
bool LinkedList::listIsEmpty() {
    return headPtr == nullptr;
}


