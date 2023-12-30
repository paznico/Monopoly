/*
 * Autore file: Davide Saladino
 */
#ifndef BASETILE_H
#define BASETILE_H

#include "../Player/Player.h"

/*
 * --------------------- BaseTile abstract class ---------------------
 * This class is used to define the interface for all the tiles. It
 * is used to avoid code duplication and to permit the use of a vector
 * of different types of tiles (see GameBoard.h).
 * -------------------------------------------------------------------
 */

class BaseTile {
public:
    virtual ~BaseTile() = default;
    virtual unsigned int get_status() const = 0;
    virtual Player& get_owner() const = 0;
    virtual void buy_terrain(std::shared_ptr<Player>) = 0;
    virtual void build_house(Player&) = 0;
    virtual void build_hotel(Player&) = 0;
    virtual void reset() = 0;
    virtual std::string get_type() const = 0;
};

#endif