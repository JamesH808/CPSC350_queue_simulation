#include "student.h"
Student::Student(){
    arrivalTime = 0;
    waitTime = 0;
    totalWaitTime = waitTime;
    windowIndex = 0;
    isFinished = false;
    indexOrder = -1;
}


Student::Student(string order, int orderIndex, int arrivalMin){
    arrivalTime = arrivalMin;
    waitTime = 0;
    totalWaitTime = waitTime;
    windowIndex = 0;
    isFinished = false;
    indexOrder = orderIndex;
    setOrder(order);

}


Student::~Student(){}


void Student::setOrder(string order)
{
    string* values = cutByChar(order, ' ');
    minutes[0] = stoi(values[0]);
    minutes[1] = stoi(values[1]);
    minutes[2] = stoi(values[2]);
    first = values[3][0];
    second = values[4][0];
    third = values[5][0];
}


/*this will parse into individual values so setOrder can assign first 3 as 
int valued wait times and the windows as chars*/
string* Student::cutByChar(string order, char c)
{
    string toCut(1,c);
    order = order.append(toCut); //put a c at the end so that it can be cut correctly
    string* values = new string[6];
    int indexStart = 0;
    for (int i = 0; i < 6; ++i) {
        values[i] = order.substr(indexStart,order.find(c,indexStart)-indexStart);
        indexStart = order.find(c,indexStart)+1;
    }
    return values;
}


/*returns the next window that the student needs to go to and increments windo index*/
char Student::nextWindow()
{
    windowIndex++;
    switch(windowIndex)
    {
        case 1: //at first next is second
            return second;
        case 2: //at second next is third
            return third;
        case 3: //at third next the student leaves the simulation
            //leave simulation
            isFinished = true;
            return 'N';
        default:
            //left blank on purpose`
            break;
    }
    //this value with never be returned
    return 'N';
}

int Student::increaseIdleTime()
{
    return waitTime++;
}

int Student::getMinutes()
{
    if(isFinished) return 0;
    return minutes[windowIndex];
}
int Student::getIndexOrder() const
{
    return indexOrder;
}
int Student::getWaitTime()
{
    return waitTime;
}
int Student::getTotalWaitTime()
{
    return totalWaitTime;
}
int Student::getArrivalTime() const
{
    return arrivalTime;
}
void Student::setArrivalTime(int time)
{
    arrivalTime = time;
}
void Student::resetWaitTime()
{
    //student has entered a new line so reset the wait time counter for the window
    totalWaitTime += waitTime;
    waitTime = 0;
}

bool operator< (const Student &c1, const Student &c2)
{
    if(c1.getIndexOrder() < c2.getIndexOrder()) return true;
    else return false;
}
/*
 * The > operator is overridden to compare the arrival times of the customers, it is still using then < method to compare
 */
//override the greater than operator to check the arrival time instead of the order index
bool operator> (const Student &c1, const Student &c2)
{
    if(c1.getArrivalTime() < c2.getArrivalTime()) return true;
    else return false;
}
