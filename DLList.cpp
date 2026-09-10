//
// Created by dinoyoshi on 9/9/26.
//

#include "DLList.h"

// Time Complexity: O(1)
template<typename T>
DLList<T>::DLList() {
    this->numNodes = 0;
    this->head = NULL;
    this->tail = NULL;
}

// Time Complexity: O(1)
template<typename T>
bool DLList<T>::PushFront(T data) {

    // if list empty
    if (this->head == NULL) {
        this->head = this->tail = new Node();
        this->head->data = this->tail->data = data;
        this->head->next = NULL;
        this->tail->next = NULL;
        this->tail->prev = NULL;
        numNodes++;
        return true;

    }

    // if list not empty
    Node *temp = this->head;
    this->head = new Node();
    this->head->data = data;
    this->head->next = temp;
    this->head->prev = NULL;
    temp->prev = this->head;
    numNodes++;
    return true;

}

// Time Complexity: O(1)
template<typename T>
bool DLList<T>::PushBack(T data) {
    // empty case

    if (this->tail == NULL) {
        this->head = this->tail = new Node();
        this->head->data = this->tail->data = data;
        this->head->next = NULL;
        this->tail->next = NULL;
        this->tail->prev = NULL;
        numNodes++;
        return true;

    }

    // general case i.e. [4, 5, 7], data is 9

    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = this->tail;
    this->tail->next = newNode;
    this->tail = newNode;
    numNodes++;
    return true;

}

// Time Complexity: O(1)
template<typename T>
T DLList<T>::TopFront() {
    if (this->head == NULL) {
        return NULL;
    }
    return this->head->data;
}

// Time Complexity: O(1)
template<typename T>
T DLList<T>::PopFront() {
    if (this->head == NULL) {
        return NULL;
    }

    // i.e. [0] <-> [1] <-> [3] <-> [4]
    // head should go to 1, its prev should be null, its next should be 3.
    Node *tmp = this->head;
    T tmpDat = this->head->data;
    if (this->head->next == NULL) {
        this->head->prev = NULL;
        head = tail = NULL;
        delete tmp;
        numNodes--;
        return tmpDat;
    }
    head = this->head->next;
    this->head->prev = NULL;
    delete tmp;
    numNodes--;
    return tmpDat;
}

// Time Complexity: O(1)
template<typename T>
T DLList<T>::TopBack() {
    if (this->head == NULL) {
        return NULL;
    }
    return this->tail->data;
}

// Time Complexity: O(1)
template<typename T>
T DLList<T>::PopBack() {
    if (this->head == NULL) {
        return NULL;
    }

    // i.e. [0] <-> [1] <-> [3] <-> [4]
    // tail should go to 3, its prev should be 1, its next should be null.
    Node *tmp = this->tail;
    T tmpDat = this->tail->data;
    if (this->tail->prev == NULL) {
        this->tail->next = NULL;
        head = tail = NULL;
        delete tmp;
        numNodes--;
        return tmpDat;
    }
    tail = this->tail->prev; // 3
    this->tail->next = NULL;
    delete tmp;
    numNodes--;
    return tmpDat;
}

// Time Complexity: O(N)
template<typename T>
bool DLList<T>::Find(T data) {

    Node *currNode = this->head;
    while (currNode != NULL) {
        if (currNode->data == data) {
            return true;
        }
        currNode = currNode->next;
    }
    return false;
}

// Time Complexity: O(N)
template<typename T>
bool DLList<T>::Erase(T data) {
    // beem

    // empty case
    if (this->head == NULL) {
        return false;
    }

    Node *currNode = this->head;
    while (currNode != NULL) {
        if (currNode->data == data) {
            // Middle Case
            if (currNode != head && currNode != tail) {
                currNode->prev->next = currNode->next;
                currNode->next->prev = currNode->prev;
                numNodes--;
                delete currNode;
                return true;
            }
            // Beginning Case
            if (currNode == head) {
                head = currNode->next;
                if (head == NULL) {
                    tail = NULL;
                    delete currNode;
                    numNodes--;
                    return true;
                }
                currNode->next->prev = NULL;
                delete currNode;
                numNodes--;
                return true;
            }
            // End Case
            if (currNode == tail) {
                tail = currNode->prev;
                if (tail == NULL) {
                    head = NULL;
                    delete currNode;
                    numNodes--;
                    return true;
                }
                currNode->prev->next = NULL;
                delete currNode;
                numNodes--;
                return true;
            }
        }
        currNode = currNode->next;
    }
    return false;
}

// Time Complexity: O(1)
template<typename T>
bool DLList<T>::Empty() {
    if (this->head == NULL) {
        return true;
    }
    return false;
}

// Time Complexity: O(N)
template<typename T>
bool DLList<T>::AddBefore(Node * desNode, T data) {
    // empty case
    if (this->head == NULL) {
        return false;
    }

    Node *currNode = this->head;
    while (currNode != NULL) {
        if (currNode == desNode) {
            // add logic, bem, reverse erase logic

            // Middle Case
            if (currNode != head && currNode != tail) {
                Node *newNode = new Node();
                newNode->data = data; // initialize
                newNode->next = currNode; // should point next to desired node
                newNode->prev = currNode->prev; // its previous should point to what was originally desired Node's prev
                currNode->prev = newNode; // desiredNode previous shall now point to the new node behind it
                newNode->prev->next = newNode; // the new node's previous' next pointer should point to the new node.
                numNodes++;
                return true;
            }
            // Beginning Case
            if (currNode == head) {
                Node *newNode = new Node();
                newNode->data = data; // data
                newNode->next = currNode; // new Node goes before head.
                currNode->prev = newNode;
                if (head == tail) { // from 1 to 2 node list
                    head = newNode;
                    tail = currNode;
                    numNodes++;
                    return true;
                }
                head = newNode;
                numNodes++;
                return true;
            }

            // End Case
            if (currNode == tail) {
                Node *newNode = new Node();
                newNode->data = data;
                newNode->prev = tail->prev;
                newNode->prev->next = newNode;
                newNode->next = tail;
                tail->prev = newNode;
                numNodes++;
                return true;
            }

        }
        currNode = currNode->next;
    }
    return false;
}

// Time Complexity: O(N)
template<typename T>
bool DLList<T>::AddAfter(Node * desNode, T data) {
    // empty case
    if (this->head == NULL) {
        return false;
    }

    Node *currNode = this->head;
    while (currNode != NULL) {
        if (currNode == desNode) {
            // add logic, bem, reverse erase logic

            // Middle Case
            if (currNode != head && currNode != tail) {
                Node *newNode = new Node();
                newNode->data = data;
                newNode->next = currNode->next;
                newNode->prev = currNode;
                currNode->next = newNode;
                newNode->next->prev = newNode;
                numNodes++;
                return true;
            }
            // Beginning Case
            if (currNode == head) {
                Node *newNode = new Node();
                newNode->data = data;
                newNode->prev = currNode;
                newNode->next = currNode->next;
                if (currNode->next != NULL) {
                    currNode->next->prev = newNode;
                }
                currNode->next = newNode;
                if (head == tail) {
                    tail = newNode;
                    numNodes++;
                    return true;
                }
                numNodes++;
                return true;
            }

            // End Case
            if (currNode == tail) {
                Node *newNode = new Node();
                newNode->data = data;
                tail->next = newNode;
                newNode->prev = tail;
                newNode->next = NULL;
                tail = newNode;
                numNodes++;
                return true;
            }
        }
        currNode = currNode->next;
    }
    return false;
}
