/*
 *  Author: Leonardo Mosele
 */
#include "../include/Robot.h"

/*
* ----------------------- Robot implementation -----------------------
* - TODO: 
* --------------------------------------------------------------------
*/

Robot::Robot(void)
{
    static int cnt = 0; 
    this->balance = initial_balance;
    name = (cnt == 0) ? "GianmariaTheRobot" : (cnt == 1) ? "MechaMario"  : (cnt == 2) ? "CircuitFilippo" : "GennaroIlBullo";
    cnt++;
}

Robot::Robot(Robot &r)
{
    this->balance = r.balance;
    this->name = r.name;
}

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

Robot &Robot::operator=(const Robot &r)
{
    this->balance = r.balance;
    this->name = r.name;
    return *this;
}

Robot &Robot::operator=(Robot &&r)
{
    this->balance = r.balance;
    this->name = r.name;
    r.balance = 0;
    r.name.clear();
    return *this;
}

int make_choice(Robot& r)
{
    srand(time(NULL));
    int choice = (rand() % 3);
    if(choice == 0)
    {
        return 1;                               // Return 1 if the robot will buy the land or build a house (25%)
    }
    else 
    {
        return 0;                               // Return 0 if the robot will not buy the land or build a house (75%)
    }
}
