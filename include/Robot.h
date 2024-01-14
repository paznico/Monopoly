/*
* Author: Leonardo Mosele
*/
#ifndef ROBOT_H
#define ROBOT_H

#include "Player.h"

#include <ctime>
#include <stdlib.h>

class Robot : public Player 
{
    public:
        
        /* Constructors */
        Robot(void);                                            // Default constructor
        Robot(Robot&);                                          // Copy constructor
        Robot(Robot&&);                                         // Move constructor

        /* Destructor */
        ~Robot();
        
        /* Operators overloading */
        Robot& operator=(const Robot&);                         // Copy assignment
        Robot& operator=(Robot&&);                              // Move assignment

        /* Helper function */
        // Function that return the robot's choice
        // - 0 with the 75% of probability (don't buy nothing)
        // - 1 with the 75% of probability (buy the terrain, build a house or a hotel)
        unsigned int make_choice(void) const override;
};

#endif
