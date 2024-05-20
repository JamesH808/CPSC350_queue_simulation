#ifndef DSINGLELINKEDLIST_H
#define DSINGLELINKEDLIST_H
#include "dListNode.h"

template <class T>
class LinkedList{
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        ListNode<T>* trace(int pos);
        unsigned int size;
    public:
        LinkedList();
        ~LinkedList();
        void insertFront(T d);
        void insertBack(T d);

        /*used for priority queue*/
        void insertPos(T d, int index);
        ListNode<T>* getFrontNode();
        ListNode<T>* getBackNode();

        T removeFront();
        T removeBack();
        T find(T value);

        T removeNode(T value);
        T get(int index);
        bool isEmpty();
        unsigned int getSize();

        void printList(bool printLink);
};


template <class T>
LinkedList<T>::LinkedList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
    ListNode<T> *node = front;
    ListNode<T> *nodeToBeDeleted = front;
    while(node != NULL){
        nodeToBeDeleted = node->next;
        delete node;
        node = nodeToBeDeleted;
    }

}

template <class T>
void LinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
        back = node;
    } else {
    node->next = front;
    front->prev = node;
    
    }
    front = node;
    ++size;
}

template <class T>
void LinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
        front = node;
    } else{
        node->prev = back;
        back->next = node;
    }
    back = node;
    size++;
}

template<typename T>
void LinkedList<T>::insertPos(T data, int index)
{
    //if out of bounds or empty add to back
    if(index >= size || isEmpty())
    {
        insertBack(data);
        return;
    }
    //if the index provided is zero of less add to front
    else if(index <= 0)
    {
        insertFront(data);
        return;
    }

    ListNode<T>* n = new ListNode<T>(data);
    ListNode<T>* traceNode = trace(index);
    traceNode->prev->next = n;
    n->prev = traceNode->prev;
    n->next = traceNode;
    traceNode->prev = n;
    size++;
}

template<typename T>
ListNode<T>* LinkedList<T>::trace(int pos)
{
    ListNode<T>* traceNode = front;
    for (int i = 0; i < pos; ++i) {
        traceNode = traceNode->next;
    }
    return traceNode;
}

template <typename T>
ListNode<T>* LinkedList<T>::getFrontNode()
{
    return front;
}
template <typename T>
ListNode<T>* LinkedList<T>::getBackNode()
{
    return back;
}

template <class T>
T LinkedList<T>::removeFront(){
    if(isEmpty()){
        cerr << "List is empty" << endl;
    } else if(size == 1){
        /*HELP______________________________*/
        
    }

    ListNode<T> *ft = front; 

    if(front->next == NULL){
        back = NULL;
    } else{
        //node to be removed is not the only one
        front->next->prev = NULL;
    }

    front = front->next;
    ft->next = NULL; 
    T data = ft->data;
    delete ft;
    size--;

    return data;
}

template <class T>
T LinkedList<T>::removeBack(){
    if(isEmpty()){
        cerr << "List is empty" << endl;
    }

    ListNode<T> *temp = back;

    if(back->prev == NULL){
        front = NULL;

    } else {
        //more than one node in list
        back->prev->next = NULL;
    }
    back = back->prev;
    temp->prev = NULL;
    T data = temp->data;
    --size;
    delete temp;

    return data;
}

template <class T>
T LinkedList<T>::find(T value){
    int pos = -1;
    ListNode<T> *curr = front;
    while(curr != NULL){
        ++pos;
        if(curr->data == value){
            break;
        }
        curr = curr->next;
    }
    if(curr == NULL){
        pos = -1;
    }
    
    return pos;
}

template <class T>
T LinkedList<T>::removeNode(T value){
    if(isEmpty()){
        throw runtime_error("is empty");
    }

    ListNode<T> *curr = front;
    while(curr->data != value){
        curr = curr->next;
        if(curr->data == NULL){
            return -1;
        }
        
    }

    if(curr == front){
        front = curr->next;
        front->prev = NULL;

    } else if (curr == back){
        back = curr->prev;
        back->next = NULL;

    } else {
        //node is inbetween front and back
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    curr->next = NULL;
    curr->prev = NULL;
    int temp = curr->data;
    --size;
    delete curr;
    return temp;

}

template <class T>
unsigned int LinkedList<T>::getSize(){
    return size;
}

template <class T>
T LinkedList<T>::get(int index){
    ListNode<T>* traceNode = front;
    for (int i = 0; i < index; ++i) {
        traceNode = traceNode->next;
    }

    return traceNode->data;

}



template <class T>
bool LinkedList<T>::isEmpty(){
    return(size == 0);
}

template <class T>
void LinkedList<T>::printList(bool printLink) {
    ListNode<T> *curr = front; 

    while (curr != nullptr) {
        // Print the data in the current node
        cout << curr->data;

        if (printLink) {
            // If printLink is true, also print the links (pointers)
            cout << " -> ";
            if (curr->next != nullptr) {
                cout << curr->next->data;
            } else {
                cout << "nullptr"; // Indicates the end of the list
            }

            cout << " (prev: ";
            if (curr->prev != nullptr) {
                cout << curr->prev->data;
            } else {
                std::cout << "nullptr"; // Indicates the start of the list
            }
            std::cout << ")";
        }

        std::cout << std::endl;

        curr = curr->next; // Move to the next node
    }
}





#endif