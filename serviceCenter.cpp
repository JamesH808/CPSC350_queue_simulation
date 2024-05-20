#include "serviceCenter.h"
#include "ListQueue.h"


serviceCenter::serviceCenter(){
    studentAverage = 0;
    studentMax = 0;
    studentAbove10 = 0;
    windowAverage = 0;
    windowMax = 0;
    windowAbove5 = 0;
}



serviceCenter::~serviceCenter(){
   
}


void serviceCenter::readFile(string inFile){
    ifstream file(inFile);

    int regWindowOpen, cashWindowOpen, finWindowOpen;
    string line1, line2, line3, line4;

    /*hard code the first 3 lines into variables*/
    if (getline(file, line1) && getline(file, line2) && getline(file, line3)) {
        
        regWindowOpen = stoi(line1);
        cashWindowOpen = stoi(line2);
        finWindowOpen = stoi(line3);

    } else {
        cerr << "Error reading lines from file." << endl;
    }

    /*create the offices, and how many windows will be open*/
    Office offices[3];
    offices[0] = Office(regWindowOpen);
    offices[1] = Office(cashWindowOpen);
    offices[2] = Office(finWindowOpen);

    string line;
    int firstMin = 0; //the min the simulation starts on
    int totalCount = 0;

    ListQueue<Student> students;

    while(getline(file,line)) {
        if(file.eof()) continue;
        //get min
        int currentMin = stoi(line);
        if(firstMin == 0) firstMin = currentMin;
        //get the next line
        getline(file,line);
        //get number of students arriving
        int studentCount = stoi(line);
        totalCount += studentCount;

        //set student schedule
        for (int i = 0; i < studentCount; ++i) {
            getline(file,line);
            students.insert(Student(line, i, currentMin));
        }
    }
    file.close();

   

    /*start the simulation*/
    simulation(offices,firstMin,totalCount,students.popAll());

    //print everything
    int index = 0;
    for (int p=0; p < 3; p++) {

        Office& office = offices[p];
        offices[p].getStats(studentAverage, windowAverage, studentMax, windowMax);
        string name;
        //find the correct office name
        if(index == 0)
        {
            name = "Registrar's ";
        }
        else if(index == 1)
        {
            name = "Cashier's ";
        }
        else
        {
            name = "Financial Aid ";
        }

        /*cout suddenly became ambiguous after changing something lol, had to put std::*/
        std::cout << name << "Office: " << endl;
        std::cout << "Mean student wait time: " << studentAverage << " tick(s)" << endl;
        std::cout << "Mean window idle time: " << windowAverage << " tick(s)" << endl;
        std::cout << "Longest student wait time: " << studentMax << " tick(s)" << endl;
        std::cout << "Longest window idle time: " << windowMax << " tick(s)" << endl;
        windowAbove5 += office.getTimeAbove5();
        index++;
        std::cout << endl;
    }
    std::cout << "Number of students waiting over 10 minutes across all offices: " << studentAbove10 << " tick(s)" << endl;
    std::cout << "Number of windows idle for over 5 minutes across all offices: " << windowAbove5 << " tick(s)" << endl;

}


void serviceCenter::simulation(Office* offices,int firstMin, int studentCount, Student* student)
{
    int min = firstMin;
    //number of students who have completed their rounds
    int studentsFinished = 0;

    //add students to their starting line
    for (int i = 0; i < studentCount; ++i) {
        OrderOfficeLines(offices, student[i], student[i].first, studentsFinished);
    }

    PQueue<Student> finishedAtWindow(true); //priority queue of students how have finished, in order of where they are in the file
    while(studentsFinished != studentCount) //until no students are left
    {
        //set all the student arrivalHour to be the currentHour if they have arrived
        for (int i = 0; i < studentCount; ++i) {
            if(student[i].getArrivalTime() <= min)
            {
                student[i].setArrivalTime(min);
            }
        }

        for (int i = 0; i < 3; ++i) { //for the three offices
            for (int j = 0; j < offices[i].getWindowSize(); ++j) { //the number of windows in each office
                offices[i].callToWindow(min);
            }
            offices[i].simulationCycle(finishedAtWindow, min);
        }
        int finishedSize = finishedAtWindow.getSize();
        for (int i = 0; i < finishedSize; ++i) {
            Student curr = finishedAtWindow.pop();
            char nextWindow = curr.nextWindow();
            //force the student to leave the simulation if their next window has time 0
            if(curr.getMinutes() == 0) nextWindow = 'N';
            OrderOfficeLines(offices, curr, nextWindow, studentsFinished);
        }
        min++;
    }
    //cout << min << endl;
}

/*add the student to the correct line based on what office they need to visit*/
void serviceCenter::OrderOfficeLines(Office* offices, Student& curr, char office, int& studentsFinished)
{
    switch(office)
    {
        case 'R':
            offices[0].addToLine(curr);
            break;
        case 'C':
            offices[1].addToLine(curr);
            break;
        case 'F':
            offices[2].addToLine(curr);
            break;
        case 'N':
            //the student has finished their windows
            studentsFinished++;
            //check to see if wait time was above 10
            if(curr.getTotalWaitTime() >= 10) studentAbove10++;
            break;
        default:
            
            break;
    }
}