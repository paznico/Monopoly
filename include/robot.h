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
        
        /* Constructor */
        Robot(void);              // default
        Robot(Robot&);            // copy
        Robot(Robot&&);           // move

        /* Destructor */
        ~Robot();
        
        /* Operator overloading */
        Robot& operator=(const Robot&);                       // Assegnamento di copia
        Robot& operator=(Robot&&);                            // Assegnamento di spostamento

        /*
        Funzione che ritorna 0 o 1 per l'acquisto di un terreno di una casa o di un hotel.
        Attenzione! CHIAMARE FUNZIONE SOLO CON TERRENO DEL ROBOT O DI NESSUNO
        */
        bool make_choice(void);
};

#endif