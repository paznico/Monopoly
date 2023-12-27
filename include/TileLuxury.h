/*
 * Autore file: Pasetto Niccolò
 */
#ifndef LUXURY_TILE_H
#define LUXURY_TILE_H

#include <iostream>
#include "Tile.h"

/*
 * Classe che descrive una casella di tipo 'lussuosa' del Monopoly.
 * Eredita i metodi base dalla classe madre 'Tile.h', sovrascrivendo
 * quelli necessari.
 */
class TileLuxury: public Tile 
{
    private:
    /*
        Player* owner;
        unsigned int status;
    */

    public:
        /* Costanti di classe */
        const unsigned int cost_terrain = 20;                   // Costo acquisto terreno
        const unsigned int cost_house = 10;                     // Costo costruzione casa
        const unsigned int cost_hotel = 10;                     // Costo costruzione hotel
        const unsigned int rent_house = 7;                      // Costo pernottamento con casa
        const unsigned int rent_hotel = 14;                     // Costo pernottamento con hotel

        /* Costruttori di classe */
        TileLuxury(void);                                       // Default
        TileLuxury(TileLuxury&);                                // Copia
        TileLuxury(TileLuxury&&);                               // Spostamento

        /* Operator overloading */
        TileLuxury& operator=(const TileLuxury&);               // Assegnamento di copia
        TileLuxury& operator=(TileLuxury&&);                    // Assegnamento di spostamento

        /* Getters di classe */
        
        const Player& get_owner(void) const;                    // Ritorna proprietario
        const unsigned int get_status(void) const;              // Ritorna lo stato della proprietà

        /* Funzioni di classe */
        void buy_property(const Player&) override;              // Acquista proprietà se disponibile
        void build_house(const Player&) override;               // Costruisce casa, se il giocatore possiede la proprietà
        void build_hotel(const Player&) override;               // Costruisce albergo, se il giocatore possiede una casa
        /* Distruttore di classe */
        ~TileLuxury();
};

/* Operator overloading */
std::ostream& operator<<(std::ostream&, const TileLuxury&);     // Output su stream

#endif
