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
        // Costo acquisto terreno
        const unsigned int cost_terrain = 6;
        // Costo costruzione casa
        const unsigned int cost_house = 3;
        // Costo costruzione hotel
        const unsigned int cost_hotel = 3;
        // Costo pernottamento con casa
        const unsigned int rent_house = 2;
        // Costo pernottamento con hotel
        const unsigned int rent_hotel = 4;

        /* Costruttori di classe */
        // Default
        TileCheap(void);
        // Copia
        TileCheap(TileCheap&);
        // Spostamento
        TileCheap(TileCheap&&);

        /* Operator overloading */
        // Assegnamento di copia
        TileCheap& operator=(const TileCheap&);
        // Assegnamento di spostamento
        TileCheap& operator=(TileCheap&&);

        /* Getters di classe */
        // Ritorna proprietario
        const Player& get_owner(void) const;
        // Ritorna lo stato della proprietà
        const unsigned int get_statut(void) const;

        /* Funzioni di classe */
        // Acquista proprietà se disponibile
        void buy_property(const Player&) override;
        // Costruisce casa, se il giocatore possiede la proprietà
        void build_house(const Player&) override;
        // Costruisce albergo, se il giocatore possiede una casa
        void build_hotel(const Player&) override;
        // Resetta la casella
        void reset(void) override;

        /* Distruttore di classe */
        ~TileCheap();
};

/* Operator overloading */
// Output su stream
std::ostream& operator<<(std::ostream&, const TileCheap&);

#endif
