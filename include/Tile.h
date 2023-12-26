#ifndef TILE_H
#define TILE_H

#include "Player.h"

class Tile
{
    private:
        int status;
        Player& owner;

    public:

        /* Constructors */
        // Default
        Tile(void);
        // Copia
        Tile(Tile&);
        // Spostamento
        Tile(Tile&&);

        /* Getters */
        const Player& get_owner(void) const;
        int get_status(void) const;

        /* Set functions */
        void set_owner(Player&);
        // ?
        void set_status(Player&);
        // ?
        virtual void buy_property(const Player&) = 0;
        virtual void build_house(const Player&) = 0;
        virtual void build_hotel(const Player&) = 0;

};

#endif
