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
        // Costo acquisto terreno
        const unsigned int cost_terrain = 20;
        // Costo costruzione casa
        const unsigned int cost_house = 10;
        // Costo costruzione hotel
        const unsigned int cost_hotel = 10;
        // Costo pernottamento con casa
        const unsigned int rent_house = 7;
        // Costo pernottamento con hotel
        const unsigned int rent_hotel = 14;

        /* Costruttori di classe */
        // Default
        TileLuxury(void);
        // Copia
        TileLuxury(TileLuxury&);
        // Spostamento
        TileLuxury(TileLuxury&&);

        /* Operator overloading */
        // Assegnamento di copia
        TileLuxury& operator=(const TileLuxury&);
        // Assegnamento di spostamento
        TileLuxury& operator=(TileLuxury&&);

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
        ~TileLuxury();
};

/* Operator overloading */
// Output su stream
std::ostream& operator<<(std::ostream&, const TileLuxury&);

#endif
