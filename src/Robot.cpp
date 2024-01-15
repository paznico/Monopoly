/*
 *  Author: Leonardo Mosele
 */
#include "../include/Robot.h"

Robot::Robot(void)
{
    static int cnt = 0;
    this->balance = initial_balance;
    // Assign different name in order from 0 to 3
    name = (cnt == 0) ? "Giocatore 1" : (cnt == 1) ? "Giocatore 2"  : (cnt == 2) ? "Giocatore 3" : "Giocatore 4";
    cnt++;
}

Robot::Robot(Robot &r)
{
    // Assigns the name and balance values ​​to the robot equal to those passed as @param values
    this->balance = r.balance;
    this->name = r.name;
}

Robot::Robot(Robot &&r)
{
    // Move the balance and name values from the @param robot to another robot
    this->balance = r.balance;
    this->name = r.name;
    r.name.clear();
    r.balance = 0;
}

Robot::~Robot()
{
    // Delete the robot
    this->balance = 0;
    this->name = "";
}

Robot &Robot::operator=(const Robot &r)
{
    // Equals two robots by checking whether they have the same name and balance
    this->balance = r.balance;
    this->name = r.name;
    return *this;
}

Robot &Robot::operator=(Robot &&r)
{
    // Commentare questo per favore
    this->balance = r.balance;
    this->name = r.name;
    r.balance = 0;
    r.name.clear();
    return *this;
}

unsigned int Robot::make_choice(void) const
{
    int choice = (rand() % 3);
    if(choice == 0)
        return 1;                               // Return 1 if the robot will buy the land or build a house (25%)
    else
        return 0;                               // Return 0 if the robot will not buy the land or build a house (75%)
}
