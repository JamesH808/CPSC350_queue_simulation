#include "window.h"

window::window()
{
    waitTime = 0;
    studentTime = 0;
    isAttended = false;
}
window::~window(){}

//set a student to the window
void window::attendWindow(Student c)
{
    isAttended = true;
    currStudent = c;
    studentTime = c.getMinutes();
}

bool window::attended()
{
    return isAttended;
}

void window::increaseIdleTime()
{
    waitTime++;
}

bool window::decreaseStudentTime()
{
    studentTime--;
    if(studentTime <= 0)
    {
        //finished at window
        return true;
    }
    return false;
}

int window::getIdleTime()
{
    return waitTime;
}

Student window::getStudent()
{
    return currStudent;
}

/*reseting the student's wait time for a new window*/
void window::leaveWindow()
{
    currStudent.resetWaitTime(); 
    isAttended = false;
}