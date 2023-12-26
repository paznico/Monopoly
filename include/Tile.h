#ifndef CASELLA_H
#define CASELLA_H

#include "Player.h"

class Tile
{
    private:
        int status;
        Player& owner;


    public:

        /* Constructors */
        Tile(void);             // default 
        Tile(Tile&);            // copy
        Tile(Tile&&);           // move
        

        /* Getters */
        Player& get_owner(void) { return owner; }
        int get_status(void) { return status; }

        /* Set functions */
        void set_owner(Player&);
        void set_status(Player&);
        virtual void buy_property(const Player&) = 0;
        virtual void build_house(const Player&) = 0;
        virtual void build_hotel(const Player&) = 0;


        
};



// Casella:
//     Variabili
//         Costanti (pubbliche)
//         Player owner
//         int status
//             0 free
//             1 bought property
//             2 house
//             3 hotel

//     Funzioni
//         get_owner
//         set_owner
//         get_status
//         buy_property(const Player&)
//         build_house
//         build_hotel

#endif