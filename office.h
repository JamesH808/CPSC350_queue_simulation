#ifndef OFFICE_H
#define OFFICE_H

#include "window.h"
#include "PQueue.h"
#include <cmath>


class Office{
    public:
        Office();
        Office(int numWindows);
        virtual ~Office();

        void addToLine(Student s);
        void callToWindow(int currentMin);
        void simulationCycle(PQueue<Student>& finishedQueue, int currentHour);

        int getWindowSize();
        void getStats(double& studentAverage, double& windowNum, int& studentMax, int& windowMax);
        int getWindowIdleTimes();
        int getWindowMax();
        int getTimeAbove5();

    private:
    int studentWaitTime;
    int studentsServed;
    int studentmax;

    int windowSize;
    window* wList;
    PQueue<Student>* line;


        

};




#endif