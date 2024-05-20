#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;


class Student{
    public:
        Student();
        Student(string order, int orderIndex, int arrivalMin);
        virtual ~Student();

        void setOrder(string order);
        string* cutByChar(string order, char c);
        bool isFinished;
        char nextWindow();

    //INDEX
    //0 = R
    //1 = C
    //2 = F
    int minutes[3];
    char first, second, third;
    int arrivalTime;

    /*lots of functions for wait times*/
    int increaseIdleTime();
    int getIndexOrder() const;
    int getWaitTime();
    int getTotalWaitTime();
    int getArrivalTime() const;
    void setArrivalTime(int time);
    void resetWaitTime();
    int getMinutes();

    
    friend bool operator< (const Student& c1, const Student& c2);
    friend bool operator> (const Student& c1, const Student& c2);

    private: 
        int windowIndex; //used to determine which window the customer is currently visiting
        int waitTime;
        int totalWaitTime;
        int indexOrder;
};



#endif


/* student->service->office->window each office has a queue */
/* to count time spent at a window just do a while loop for how long they stay there */
/*students go into a queue and then go to office then to window*/
/* simulate windows as an array*/