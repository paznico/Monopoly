#ifndef ROBOT_H
#define ROBOT_H

#include "Player.h"

class Robot : public Player 
{
    private:
        // altro

    public:
        
        /* Constructor */
        Robot(void);               // default
        Robot(Player&);            // copy
        Robot(Player&&);           // move

        
        void dice_throw() override;
};

#endif