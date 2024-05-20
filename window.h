#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "student.h"
using namespace std;

class window{
    public:
        window();
        ~window();

        bool attended();
        void attendWindow(Student c);
        void increaseIdleTime();
        bool decreaseStudentTime(); //returns the next window for the student

        Student getStudent();
        void leaveWindow();
        int getIdleTime();

    private:
    Student currStudent;
    int studentTime;
    int waitTime;
    bool isAttended;

};



#endif
