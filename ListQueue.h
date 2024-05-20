#ifndef LISTQUEUE_H
#define LISTQUEUE_H
#include "dLinkedList.h"

template <class T>
class ListQueue{
    public: 
        ListQueue(); //default constructor
        ~ListQueue(); // destructor

        //corefunctions
        void insert(T d);
        T remove();
        T* popAll();


        //aux functions
        bool isEmpty();
        unsigned int Size();
        void print(bool details);

    private: 
        LinkedList<T>* dlist;
        int mSize;
        unsigned int front;
        unsigned int rear;
        unsigned int numElements;
       



};


template <class T>
ListQueue<T>::ListQueue(){
    mSize = 0;
    dlist = new LinkedList<T>();
}


template <class T>
ListQueue<T>::~ListQueue(){
    delete dlist;
}

template <class T>
void ListQueue<T>::insert(T d){

    dlist->insertBack(d);
}

template <class T>
T ListQueue<T>::remove(){
     if(isEmpty()){
        throw runtime_error("Queue is empty");
    }
    return dlist->removeFront();
}



template <class T>
bool ListQueue<T>::isEmpty(){
    return (dlist->isEmpty());
}

template <class T>
unsigned int ListQueue<T>::Size(){
    return dlist->getSize();
}

template <class T>
void ListQueue<T>::print(bool details){
    dlist->printList(details);
}

template <typename T>
T* ListQueue<T>::popAll()
{
    int s = Size();
    T* values = new T[s];
    for (int i = 0; i < s; ++i)
    {
        values[i] = remove();
    }
    return values;
}


#endif