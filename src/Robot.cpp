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
    name = (cnt == 0) ? "Giocatore 1" : (cnt == 1) ? "Giocatore 2"  : (cnt == 2) ? "Giocatore 3" : "Giocatore 4";
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

bool make_choice(void)
{
    srand(time(NULL));
    int choice = (rand() % 3);
    if(choice == 0)
        return true;                               // Return 1 if the robot will buy the land or build a house (25%)
    else
        return false;                               // Return 0 if the robot will not buy the land or build a house (75%)
}
