/*
 * Autore file: Pasetto Niccolò
 */
#ifndef TILE_CHEAP_H
#define TILE_CHEAP_H

#include <iostream>
#include "Tile.h"

/*
 * Classe che descrive una casella di tipo 'economica' del Monopoly.
 * Eredita i metodi base dalla classe madre 'Tile.h', sovrascrivendo
 * quelli necessari.
 */
class TileCheap: public Tile 
{
    private:
    /*
        Player* owner;
        unsigned int status;
    */

    public:
        /* Costanti di classe */
        const unsigned int cost_terrain = 6;                        // Costo acquisto terreno
        const unsigned int cost_house = 3;                          // Costo costruzione casa
        const unsigned int cost_hotel = 3;                          // Costo costruzione hotel
        const unsigned int rent_house = 2;                          // Costo pernottamento con casa
        const unsigned int rent_hotel = 4;                          // Costo pernottamento con hotel

        /* Costruttori di classe */
        TileCheap(void);                                            // Default
        TileCheap(TileCheap&);                                      // Copia
        TileCheap(TileCheap&&);                                     // Spostamento

        /* Operator overloading */
        TileCheap& operator=(const TileCheap&);                     // Assegnamento di copia
        TileCheap& operator=(TileCheap&&);                          // Assegnamento di spostamento

        /* Getters di classe */
        const Player& get_owner(void) const;                        // Ritorna proprietario
        const unsigned int get_statut(void) const;                  // Ritorna lo stato della proprietà

        /* Funzioni di classe */
        void buy_property(const Player&) override;                  // Acquista proprietà se disponibile
        void build_house(const Player&) override;                   // Costruisce casa, se il giocatore possiede la proprietà
        void build_hotel(const Player&) override;                   // Costruisce albergo, se il giocatore possiede una casa

        /* Distruttore di classe */
        ~TileCheap();
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const TileCheap&);          // Output su stream

#endif
