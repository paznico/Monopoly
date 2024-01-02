/*
 *  Author: Leonardo Mosele
 */
#include "Robot.h"

/*
* ----------------------- Robot implementation -----------------------
* - TODO: 
* --------------------------------------------------------------------
*/

Robot::Robot(void)
{
    static int cnt = 0; 
    this->balance = initial_balance;
    name = (cnt == 0) ? "GianmarcoTheRobot" : (cnt == 1) ? "MechaMario"  : (cnt == 2) ? "CircuitFilippo" : "GennaroIlBullo";
    cnt++;
}

/*
Robot::Robot(Robot &r)
{
    this->balance = r.balance;
    this->name = r.name;
}
*/

Robot::Robot(Robot &&r)
{
    this->balance = r.balance;
    this->name = r.name;
    r.name.clear();
    r.balance = 0;
}

Robot::~Robot()
{
    this->balance = 0;
    this->name = "";
}

/*
Robot &Robot::operator=(const Robot &r)
{
    this->balance = r.balance;
    this->name = r.name;
    return *this;
}
*/

Robot &Robot::operator=(Robot &&r)
{
    this->balance = r.balance;
    this->name = r.name;
    r.balance = 0;
    r.name.clear();
    return *this;
}

int make_choice(Robot& r, int status)
{
    srand(time(NULL));
    int choice;
    if(status == 0)
    {
        choice = (rand() % 3);
        if(choice == 0)
        {
            return 1;                                           // the terrain has no owner, so the robot will buy it
        }
        else
        {
            return 0;                                           // the terrain has no owne but the robot will not buy it
        }
    }
    else if(status == 1)                                        // the house 
    {
        choice = (rand() % 3);
        if(choice == 0)
        {
            return 1;                                           // the robot is the 
        }
        else
        {
            return 0;
        }
    }
}