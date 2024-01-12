/*
 * Autore file: Leonardo Mosele
 */
#ifndef BASETILE_H
#define BASETILE_H

#include "Player.h"
#include <memory>

/*
 * --------------------- BaseTile abstract class ---------------------
 * This class is used to define the interface for all the tiles. It
 * is used to avoid code duplication and to permit the use of a vector
 * of different types of tiles (see GameBoard.h).
 * -------------------------------------------------------------------
 */

class BaseTile {
public:
    virtual unsigned int get_status() const = 0;
    virtual std::shared_ptr<Player> get_owner() const = 0;

    virtual std::string get_coord(void) const = 0;

    virtual void buy_terrain(std::shared_ptr<Player>) = 0;
    virtual void build_house(std::shared_ptr<Player>) = 0;
    virtual void build_hotel(std::shared_ptr<Player>) = 0;
    virtual void pay_rent_house(std::shared_ptr<Player>) = 0;
    virtual void pay_rent_hotel(std::shared_ptr<Player>) = 0;

    virtual void reset() = 0;
    virtual std::string get_type() const = 0;
};

#endif