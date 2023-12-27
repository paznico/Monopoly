/*
 * Autore file: Leonardo Mosele
 */
#ifndef STANDARD_TILE_H
#define STANDARD_TILE_H

#include <iostream>
#include "Tile.h"

/*
 * Classe che descrive una casella di tipo 'standard' del Monopoly.
 * Eredita i metodi base dalla classe madre 'Tile.h', sovrascrivendo
 * quelli necessari.
 */
class TileStandard: public Tile 
{
    private:
    /*
        Player* owner;
        unsigned int status;
    */

    public:
        /* Costanti di classe */
        const unsigned int cost_terrain = 10;                       // Costo acquisto terreno
        const unsigned int cost_house = 5;                          // Costo costruzione casa
        const unsigned int cost_hotel = 5;                          // Costo costruzione hotel
        const unsigned int rent_house = 4;                          // Costo pernottamento con casa
        const unsigned int rent_hotel = 8;                          // Costo pernottamento con hotel

        /* Costruttori di classe */
        TileStandard(void);                                         // Default
        TileStandard(TileStandard&);                                // Copia
        TileStandard(TileStandard&&);                               // Spostamento

        /* Operator overloading */
        TileStandard& operator=(const TileStandard&);               // Assegnamento di copia
        TileStandard& operator=(TileStandard&&);                    // Assegnamento di spostamento

        /* Getters di classe */
        
        const Player& get_owner(void) const;                        // Ritorna proprietario
        const unsigned int get_status(void) const;                  // Ritorna lo stato della proprietà

        /* Funzioni di classe */
        void buy_property(const Player&) override;                  // Acquista proprietà se disponibile
        void build_house(const Player&) override;                   // Costruisce casa, se il giocatore possiede la proprietà
        void build_hotel(const Player&) override;                   // Costruisce albergo, se il giocatore possiede una casa

        /* Distruttore di classe */
        ~TileStandard();
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const TileStandard&);       // Output su stream

#endif
