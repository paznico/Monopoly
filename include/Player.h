/*
 *  Author: Nicolò Pasetto
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <random>

/*
 * Descrizione classe
 */
class Player 
{
    protected:
        const unsigned int initial_balance = 100;               // Costante che definice il bilancio iniziale
        unsigned int balance;                                   // Saldo disponibile
        std::string name;                                       // Nome giocatore

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
        // Serve?  <- Si
        
        /* Getters */
        unsigned int get_balance(void) const;                   // Ritorna il conto disponibile
        std::string get_name(void) const;                       // Ritorna il nome del giocatore

        /* Setters */
    
        void set_balance(int);                                  // Modifica il conto disponibile

        /* Funzioni di classe */
        unsigned int dice_throw(void) const;                    // Funzione che simula il lancio di un dado
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const Player&);         // Output sullo stream

bool operator==(const Player&, const Player&);                  // Uguaglianza

bool operator!=(const Player&, const Player&);                  // Disuguaglianza

#endif
