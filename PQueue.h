#ifndef P_QUEUE_H
#define P_QUEUE_H

#include "dLinkedList.h"

template <typename T>
class PQueue: private LinkedList<T>{ //priority queue to interact with linked list directly altering, not a copy
public:
    PQueue(bool isMin); //min queue or not
    virtual ~PQueue();

    void push(T data);
    void push(T data, bool orderOfArrival);
    T pop();
    T peek();

    int getSize();
    bool isEmpty();

    T* popAll(); //return array pointer of all data in the Pqueue
private:
    bool isMinQueue;
};

template <typename T>
bool PQueue<T>::isEmpty(){
    return LinkedList<T>::isEmpty();
}

template <typename T>
int PQueue<T>::getSize(){
    return LinkedList<T>::getSize();
}

template <typename T>
PQueue<T>::PQueue(bool isMin){
    isMinQueue = isMin;
}

template <typename T>
PQueue<T>::~PQueue(){}

template <typename T>
T PQueue<T>::pop(){
    if(isMinQueue)
    {
        return LinkedList<T>::removeFront(); //smallest always at front
    } else
    {
        return LinkedList<T>::removeBack(); //largest always at back
    }
}
template <typename T>
T PQueue<T>::peek()
{
    return LinkedList<T>::get(0);
}

template <typename T>
void PQueue<T>::push(T data) {
    if (isEmpty())
    {
        LinkedList<T>::insertBack(data);
        return;
    }
    int currIdx = 0;
    ListNode<T>* currNode = LinkedList<T>::getFrontNode();
    while(currNode != nullptr && currNode->data < data){
        ++currIdx;
        currNode = currNode->next;
    }
    LinkedList<T>::insertPos(data, currIdx);
}

//overloaded method that compares the > symbol rather than the < symbol
//does not use the isMinQueue variable because it is still a min queue it is just comparing a different number
template <typename T>
void PQueue<T>::push(T data, bool orderOfArrival){
    if(isEmpty())
    {
        LinkedList<T>::insertBack(data);
        return;
    }
    int currIdx = 0;
    ListNode<T>* currNode = LinkedList<T>::getFrontNode();
    while(currNode != nullptr && currNode->data > data){ //compares > rather than <
        ++currIdx;
        currNode = currNode->next;
    }
    LinkedList<T>::insertPos(data, currIdx);
}

template <typename T>
T* PQueue<T>::popAll()
{
    int size = getSize();
    T* values = new T[size];
    for (int i = 0; i < size; ++i)
    {
        values[i] = pop();
    }
    return values;
}

#endif