/*
 *  Autore: Pasetto Niccolò
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

/*
 * Classe che descrive un giocatore 'umano' per il gioco
 * del Monopoly, infatti le scelte all'interno del gioco 
 * vengono prese in input dall'utente a tempo di esecuzione
 */
class Player
{
    /*
     * Variabili di classe
     * Abbiamo deciso di usare il modificatore di accesso 'protected'
     * in modo che la classe derivata 'Robot' possa accedere a queste
     * variabili, senza tuttavia renderle pubbliche al di fuori della classe
     */
    protected:
        // Costante che definisce il bilancio iniziale
        const int initial_balance = 100;
        // Bilancio del giocatore
        int balance;
        // Nome del giocatore
        std::string name;
        // Posizione del giocatore, viene usato unsigned int
        // perchè il valore non potrà mai essere < 0
        unsigned int position;

    public:
        /* Costruttori */
        // Default
        Player(void);
        // Inizializza il nome al giocatore
        Player(std::string);
        // Copia disabilitata per evitare problemi di slicing
        Player(const Player&) = delete;
        // Spostamento
        Player(Player&&);

        /* Overloading operatori */
        // Copia disabilitata per evitare problemi di slicing
        Player& operator=(const Player&) = delete;
        // Assegnamento di spostamento
        Player& operator=(Player&&);

        /* Distruttore */
        ~Player();
        
        /* Funzioni getters */
        // Ritorna il bilancio
        int get_balance(void) const;
        // Ritorna il nome
        std::string get_name(void) const;
        // Ritorna la posizione
        int get_position(void) const;

        /* Funzioni setters */
        // Modifica il bilancio con un nuovo valore
        void set_balance(int);
        // Modifica la posizione del giocatore, quando supera
        // il 28 (ultima casella del tabellone) la posizione
        // viene fatta tornare a 0 in modo da far ripartire il ciclo
        void move(const unsigned int);

		/* Funzioni di aiuto */
        // Funzione che fa compiere una scelta al giocatore
        // La scelta viene presa in input dall'utente e può ritornare:
        //      0   Se la risposta è 'NO'
        //      1   Se la risposta è 'SI'
        //      2   Se vuole controllare il tabellone
		virtual unsigned int make_choice(void) const;
};

/* Overloading  operatori */
// Output sullo stream
std::ostream& operator<<(std::ostream&, const Player&);

#endif
