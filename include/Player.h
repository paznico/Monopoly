/*
 *  Author: Niccolò Pasetto
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

/*
 * Descrizione classe
 */
class Player 
{
    protected:
        const unsigned int initial_balance = 100;               // Costante che definice il bilancio iniziale
        unsigned int balance;                                   // Available balance
        std::string name;                                       // Player name
        int position;

    public:
        /* Constructor */
        Player(void);                                           // Default
        Player(std::string);                                    // Constructor
        Player(const Player&) = delete;                         // Copy constructor
        Player(Player&&);                                       // Move constructor

        /* Operator overloading */
        Player& operator=(const Player&) = delete;              // Copy assignment
        Player& operator=(Player&&);                            // Move assignment

        /* Destructor */
        ~Player();
        
        /* Getters */
        unsigned int get_balance(void) const;                   // Returns balance
        std::string get_name(void) const;                       // Returns name
        int get_position(void);                                 // Returns player position

        /* Setters */
        void set_balance(int);                                  // Set initial balance
        void add_balance(unsigned int);                         // Add balance
        bool sub_balance(unsigned int);                         // Subtract balance

        void move(const unsigned int);                          // Move player
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const Player&);         // Stream output

#endif
