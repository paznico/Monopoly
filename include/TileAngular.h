/*
 * Autore file: Leonardo Mosele
 */
#ifndef TILEANGULAR_H
#define TILEANGULAR_H

#include <iostream>
#include "Tile.h"

/*
 * Classe che descrive una casella di tipo 'angolare' del Monopoly.
 * Eredita i metodi base dalla classe madre 'Tile.h', sovrascrivendo
 * quelli necessari.
 */

class TileAngular : public Tile
{
    public:

        /* Constructors */
        TileAngular(void);                                             // Default
        TileAngular(Tile&);                                            // Copy
        TileAngular(Tile&&);                                           // Move
        
        void buy_property(const Player&) override {}
        void build_house(const Player&) override {}
        void build_hotel(const Player&) override {}
};

#endif
