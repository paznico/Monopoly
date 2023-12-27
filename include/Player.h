/*
 * Autore file: Leonardo Mosele
 */

#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
    protected:
        const unsigned int initial_balance = 100;
        int balance;

    public:

        /* Constructor */
        Player(void);               // default
        Player(Player&);            // copy
        Player(Player&&);           // move

        /* Destructor */
        ~Player();
        
        /* Getters */
        int get_balance(void);

        /* Setters */
        void set_balance();

        virtual void dice_throw();
};

#endif