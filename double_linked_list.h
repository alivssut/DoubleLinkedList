/*****************************************
* Shahrood User ID:  -
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include "exception.h"

class DoubleLinkedList {
public:
    class DoubleNode {
    public:
        DoubleNode(int const & = int(), DoubleNode * = nullptr, DoubleNode * = nullptr);

        int value() const;

        DoubleNode *previous() const;

        DoubleNode *next() const;

        int nodeValue;
        DoubleNode *previousNode;
        DoubleNode *nextNode;
    };

    DoubleLinkedList();

    DoubleLinkedList(DoubleLinkedList const &);

    ~DoubleLinkedList();

    // Accessors

    int size() const;

    bool empty() const;

    int front() const;

    int back() const;

    DoubleNode *begin() const;

    DoubleNode *end() const;

    DoubleNode *find(int const &) const;

    int count(int const &) const;

    // Mutators

    void swap(DoubleLinkedList &);

    void pushFront(int const &);

    void pushBack(int const &);

    void popFront();

    void popBack();

    int erase(int const &);

private:
    DoubleNode *listHead;
    DoubleNode *listTail;
    int listSize;

    // List any additional private member functions you author here
    // Friends

    friend std::ostream &operator<<(std::ostream &, DoubleLinkedList const &);
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

DoubleLinkedList::DoubleLinkedList() :
// Updated the initialization list here
        listHead(nullptr),
        listTail(nullptr),
        listSize(0) {
    // Enter your implementation here
}
/*
 * update list with input of constructor
 */
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList const &list) :
// Updated the initialization list here
        listHead(nullptr),
        listTail(nullptr),
        listSize(0) {
    DoubleNode *temp = list.listHead;
    for (temp = list.listHead; temp != nullptr; temp = temp->next()) {
        pushBack(temp->value());
    }
}
/*
 * destroy every node
 */
DoubleLinkedList::~DoubleLinkedList() {
    if (listSize == 1)popFront();
    if (empty())return;
    DoubleNode *temp = listHead;
    for (auto temp = listHead; temp != nullptr ; temp = temp->nextNode) {
        delete listHead->previousNode;
    }
    delete listHead;
}
/*
 * return th size of list
 */
int DoubleLinkedList::size() const {
    return listSize;
}
/*
 * return true or false
 */
bool DoubleLinkedList::empty() const {
    return listHead == NULL;
}
/*
 * return value of front node in list
 */
int DoubleLinkedList::front() const {
    if (empty())throw Underflow();
    return listHead->value();
}
/*
 * return value of back node in list
 */
int DoubleLinkedList::back() const {
    if (empty())throw Underflow();
    return listTail->value();
}
/*
 * return address of list head
 */
DoubleLinkedList::DoubleNode *DoubleLinkedList::begin() const {
    return listHead;
}
/*
 * return address of list tail
 */
DoubleLinkedList::DoubleNode *DoubleLinkedList::end() const {
    return listTail;
}
/*
 * find every node with input value and return count
 */
DoubleLinkedList::DoubleNode *DoubleLinkedList::find(int const &value) const {
    DoubleNode *temp = listHead;
    for (temp = listHead; temp != nullptr; temp = temp->nextNode) {
        if (temp->nodeValue == value)return temp;
    }
    return nullptr;
}
/*
 * find count of every node with input value
 */
int DoubleLinkedList::count(int const &value) const {
    int count = 0;
    DoubleNode *temp = listHead;
    for (temp = listHead; temp != nullptr; temp = temp->nextNode) {
        if (temp->nodeValue == value)count++;
    }
    return count;
}
/*
 * sawp this list with input list
 */
void DoubleLinkedList::swap(DoubleLinkedList &list) {
    DoubleNode *tempHead = listHead;
    DoubleNode *tempTail = listTail;
    int tempSize = listSize;
    listHead = list.listHead;
    listTail = list.listTail;
    listSize = list.listSize;
    list.listHead = tempHead;
    list.listTail = tempTail;
    list.listSize = tempSize;
}
/*
 * add to front of list
 */
void DoubleLinkedList::pushFront(int const &value) {
    DoubleNode *newNode = new DoubleNode();
    newNode->nodeValue = value;

    if (listHead == nullptr)
        listHead = listTail = newNode;
    else {
        listHead->previousNode = newNode;
        newNode->nextNode = listHead;
        listHead = newNode;
    }
    listSize++;

}
/*
 * add to back of list
 */
void DoubleLinkedList::pushBack(int const &value) {
    DoubleNode *newNode = new DoubleNode();
    newNode->nodeValue = value;

    if (listHead == nullptr)
        listHead = listTail = newNode;
    else {
        listTail->nextNode = newNode;
        newNode->previousNode = listTail;
        listTail = newNode;
    }
    listSize++;
}
/*
 * remove from front of list
 */
void DoubleLinkedList::popFront() {
    if (empty())throw Underflow();
    else {
        if (listSize == 1) {
            delete listHead;
            listHead = nullptr;
            listTail = nullptr;
        } else if (listSize > 1) {
            if (listHead == listTail) {
                listTail = nullptr;
            }
            listHead = listHead->nextNode;
            delete listHead->previousNode;
            listHead->previousNode = nullptr;
        }
        listSize--;
    }

}
/*
 * remove from back of list
 */
void DoubleLinkedList::popBack() {
    if (empty())throw Underflow();
    else {
        if (listSize == 1) {
            listHead = nullptr;
            listTail = nullptr;
        } else if (listSize > 1) {
            if (listHead == listTail) {
                listHead = nullptr;
            }
            listTail = listTail->previousNode;
            delete listTail->nextNode;
            listTail->nextNode = nullptr;
        }
        listSize--;
    }

}
/*
 * remove every node with input value
 */
int DoubleLinkedList::erase(int const &value) {
    int count = 0, counter = 0;
    DoubleNode *temp = listHead;
    if (empty()) {
        return 0;
    } else if (listSize == 1){
        listTail = nullptr;
        listHead = nullptr;
        listSize --;
    } else {
        for (temp = listHead; temp != nullptr; temp = temp->nextNode) {
            if (temp->nodeValue == value) {
                if (counter == 0) {
                    listHead = temp->nextNode;
                    listHead->previousNode = nullptr;
//                    delete listHead->previousNode;
                } else if (counter == listSize - 1) {
                    listTail = temp->previousNode;
                    listTail->nextNode = nullptr;
//                    delete listTail->nextNode;
                } else {
                    temp->nextNode->previousNode = temp->previousNode;
                    temp->previousNode->nextNode = temp->nextNode;
                }
                count++;
            }
            counter++;
        }
    }
    listSize -= count;
    return count;
}

DoubleLinkedList::DoubleNode::DoubleNode(
        int const &nv,
        DoubleLinkedList::DoubleNode *pn,
        DoubleLinkedList::DoubleNode *nn) :
// Updated the initialization list here
        nodeValue(0), // This assigns 'nodeValue' the default value
        previousNode(nullptr),
        nextNode(nullptr) {
}
/*
 * return value of node
 */
int DoubleLinkedList::DoubleNode::value() const {
    return nodeValue;
}
/*
 * return previous node
 */
DoubleLinkedList::DoubleNode *DoubleLinkedList::DoubleNode::previous() const {
    return previousNode;
}
/*
 * return next node
 */
DoubleLinkedList::DoubleNode *DoubleLinkedList::DoubleNode::next() const {
    return nextNode;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &out, DoubleLinkedList const &list) {
    out << "head";

    // print list from start to end
    for (auto *ptr = list.begin(); ptr != nullptr; ptr = ptr->next()) {
        out << "->" << ptr->value();
    }
    out << "->0" << std::endl << "tail";

    // print list from end to start
    for (DoubleLinkedList::DoubleNode *ptr = list.end(); ptr != nullptr; ptr = ptr->previous()) {
        out << "->" << ptr->value();
    }
    out << "->0";

    return out;
}

#endif