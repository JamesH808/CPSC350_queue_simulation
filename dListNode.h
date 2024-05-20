#ifndef DLISTNODE_H
#define DLISTNODE_H

#include <iostream>
#include <exception>
using namespace std;

template <class T> 
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        T data;
        ListNode<T> *next;
        ListNode<T> *prev;

};

template <class T>
ListNode<T>::ListNode(){}

template <class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template <class T>
ListNode<T>::~ListNode(){
    next = NULL;
    prev = NULL;
}

#endif