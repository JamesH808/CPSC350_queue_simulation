#ifndef SERVICECENTER_H
#define SERVICECENTER_H


#include "office.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;


class serviceCenter{
    public:
        serviceCenter();
        virtual ~serviceCenter();

        void readFile(string inFile);
        void simulation(Office* offices, int currentMin, int studentCount, Student* students);
        void OrderOfficeLines(Office* offices, Student& c, char office, int& studentsFinished);
        

    double studentAverage;
    int studentMax;
    int studentAbove10;
    double windowAverage;
    int windowMax;
    int windowAbove5;
        

};



#endif

