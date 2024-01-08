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
        unsigned int balance;                                   // Saldo disponibile
        std::string name;                                       // Nome giocatore
        int position;

    public:
        /* Constructor */
        Player(void);                                           // Default
        Player(std::string);                                    // Inizializza il nome
        Player(const Player&) = delete;                         // Copia
        Player(Player&&);                                       // Spostamento

        /* Operator overloading */
        Player& operator=(const Player&) = delete;              // Assegnamento di copia
        Player& operator=(Player&&);                            // Assegnamento di spostamento

        /* Destructor */
        ~Player();
        
        /* Getters */
        unsigned int get_balance(void) const;                   // Ritorna il conto disponibile
        std::string get_name(void) const;                       // Ritorna il nome del giocatore
        int get_position(void);                                 // Ritorna la posizione del giocatore

        /* Setters */
        void set_balance(int);                                  // Modifica il conto disponibile
        void add_balance(unsigned int);
        bool sub_balance(unsigned int);

        void move(const int);
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const Player&);         // Output sullo stream

#endif
