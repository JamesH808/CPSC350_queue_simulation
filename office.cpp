#include "office.h"


Office::Office(int numWindows)
{
    studentmax = 0;
    studentWaitTime = 0;
    studentsServed = 0;

    windowSize = numWindows;

    /*setting up array of windows for an office*/
    line = new PQueue<Student>(true);
    wList = new window[windowSize]();
}
Office::Office()
{
    studentmax = 0;
    studentWaitTime = 0;
    studentsServed = 0;

    windowSize = -1;

    line = new PQueue<Student>(true);
    wList = new window[1];
}
Office::~Office()
{

}

void Office::addToLine(Student s){

    /*uses the priority queue to add students in line in the order they arrive*/
    line->push(s,true);

}

/*loops through all windows in an office, if student is in line and open window they will be called*/
void Office::callToWindow(int currentMin) {
    for (int i = 0; i < windowSize; ++i) {
        //the priority queue has a student and a window is open
        if (!wList[i].attended() && !line->isEmpty()) {
            int arrivalTime = line->peek().getArrivalTime();
            //if it is during the arrival time of the student
            if(arrivalTime <= currentMin)
            {
                int time = line->peek().getWaitTime();
                studentWaitTime += time;
                studentsServed++;
                if (studentmax < time){
                    studentmax = time;
                }
                wList[i].attendWindow(line->pop());
            }
        }
    }
}

/*this is equivalent to 1 min in the simulation*/
void Office::simulationCycle(PQueue<Student>& finished, int currentHour)
{
    for (int i = 0; i < windowSize; ++i) {

        if(!wList[i].attended())
        {
            wList[i].increaseIdleTime();
        }
        else {
            if (wList[i].decreaseStudentTime())
            {
                finished.push(wList[i].getStudent());
                wList[i].leaveWindow();
            }
        }
    }
    //all the students in the line are waiting so pop all the line elements out, add one to their wait time and then
    //push them back in
    int lineSize = line->getSize();
    for (int i = 0; i < lineSize; ++i) {
        Student s = line->pop();
        //if the student hasn't arrived yet
        if(s.getArrivalTime() <= currentHour) s.increaseIdleTime();
        line->push(s);
    }
}

int Office::getWindowSize()
{
    return windowSize;
}

//set the stats of the simulation
/*using double to get floating point division and then round function to get back to a number*/
void Office::getStats(double &studentAverage, double &windowAverage, int &studentMax, int& windowMax)
{
    studentAverage = round(((double)studentWaitTime / studentsServed) * 100) / 100;
    windowAverage =  round(((double)getWindowIdleTimes() / windowSize) * 100) / 100;
    studentMax = studentmax;
    windowMax = getWindowMax();
}

//get total amount of window idle times
int Office::getWindowIdleTimes()
{
    int total = 0;
    for (int i = 0; i < windowSize; ++i) {
        total += wList[i].getIdleTime();
    }
    return total;
}


int Office::getWindowMax()
{
    int max = 0;
    for (int i = 0; i < windowSize; ++i) {
       if(max < wList[i].getIdleTime()) max = wList[i].getIdleTime();
    }
    return max;
}

//count times the window wait time was above 5
int Office::getTimeAbove5()
{
    int count = 0;
    for (int i = 0; i < windowSize; ++i) {
        if(wList[i].getIdleTime() >= 5) count++;
    }
    return count;
}