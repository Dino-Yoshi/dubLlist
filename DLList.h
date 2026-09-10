//
// Created by dinoyoshi on 9/9/26.
//

#ifndef DUBLLIST_DLLIST_H
#define DUBLLIST_DLLIST_H

/* Necessary features
* PushFront(Key)
• PushBack(Key)
• TopFront()
• PopFront()
• TopBack()
• PopBack()
• Find(Key)
• Erase(Key)
• Empty()
• AddBefore(Node, Key)
• AddAfter(Node, Key)
 */

template <typename T>
class DLList {
private:
    int numNodes;
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
public:

    DLList();
    bool PushFront(T);
    bool PushBack(T);
    T TopFront();
    T PopFront();
    T TopBack();
    T PopBack();
    bool Find(T);
    bool Erase(T);
    bool Empty();
    bool AddBefore(Node*, T);
    bool AddAfter(Node*, T);
};


#endif //DUBLLIST_DLLIST_H
