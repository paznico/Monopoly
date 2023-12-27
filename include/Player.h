#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
    private:
        int balance;

    public:

        /* Constructor */
        Player(void);               // default
        Player(Player&);            // copy
        Player(Player&&);           // move

        /* Destructor */
        ~Player();
        
        /* Getters */
        int get_balance(void) { return balance; }

        /* Setters */
        void set_balance();

        virtual void dice_throw();
};

#endif