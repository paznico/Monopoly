/*
 *
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

/*
 * Descrizione classe
 */
class Player 
{
    private:
        /* Variabili di classe */
        // Saldo disponibile
        unsigned int balance;
        // Nome giocatore
        std::string nome;

    public:
        /* Constructor */
        // Default
        Player(void);
        // Inizializza il nome
        Player(std::string);
        // Copia
        Player(const Player&);
        // Spostamento
        Player(Player&&);

        /* Operator overloading */
        // Assegnamento di copia
        Player& operator=(const Player&);
        // Assegnamento di spostamento
        Player& operator=(Player&&);

        /* Destructor */
        ~Player();
        // Serve?
        
        /* Getters */
        // Ritorna il conto disponibile
        unsigned int get_balance(void) const;
        // Ritorna il nome del giocatore
        std::string get_name(void) const;

        /* Setters */
        // Modifica il conto disponibile
        void set_balance(int);

        /* Funzioni di classe */
        // Funzione che simula il lancio di un dado
        virtual unsigned int dice_throw(void) const;
};

/* Operator overloading */
// Output sullo stream
std::ostream& operator<<(std::ostream&, const Player&);

// Uguaglianza
bool operator==(const Player&, const Player&);

// Disuguaglianza
bool operator!=(const Player&, const Player&);

#endif
