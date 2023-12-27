/*
 * Autore file: Davide Saladino
 */
#ifndef TILE_H
#define TILE_H

#include "Player.h"
#include <memory>

class Tile
{
    protected:
        int status;
        std::shared_ptr<Player> owner;

    public:

        Tile(void);                                     // Default constructor
        Tile(Tile&) = delete;                           // Deleted copy constructor
        Tile& operator=(const Tile&) = delete;          // Deleted copy assignment
        virtual ~Tile() {}                              // Virtual destructor

        /* Getters */
        const Player& get_owner(void) const;
        int get_status(void) const;

        /* Setters */
        virtual void buy_property(const Player&) = 0;
        virtual void build_house(const Player&) = 0;
        virtual void build_hotel(const Player&) = 0;

        void reset(void);                               // Clear the object
};

#endif
