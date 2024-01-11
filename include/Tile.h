/*
* Author: Davide Saladino
*/
#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <memory>
#include "Player.h"
#include "Constants.h"
#include "BaseTile.h"

/*
* ----------------------- Tile template class -----------------------
* The template seems to be the best solution to avoid code duplication
* and fits perfectly with the idea of having different types of tiles
* -------------------------------------------------------------------
*/

template <typename EnumType>
class Tile : public BaseTile{
public:
    Tile();
    Tile(const std::string&);
    Tile(const Tile&);
    Tile(Tile&&);

    unsigned int get_status(void) const override;
    std::shared_ptr<Player> get_owner(void) const override;

    Tile& operator=(const Tile&);
    Tile& operator=(Tile&&);

    void buy_terrain(std::shared_ptr<Player>) override;
    void build_house(std::shared_ptr<Player>) override;
    void build_hotel(std::shared_ptr<Player>) override;
    void pay_rent_house(std::shared_ptr<Player>) override;
    void pay_rent_hotel(std::shared_ptr<Player>) override;
    void reset(void) override;

    std::string get_type(void) const override;
    std::string get_coord(void) const { return this->coordinat; };


    const int cost_property = static_cast<int>(EnumType::COST_PROPERTY);
    const int cost_house = static_cast<int>(EnumType::COST_HOUSE);
    const int cost_hotel = static_cast<int>(EnumType::COST_HOTEL);
    const int rent_house = static_cast<int>(EnumType::RENT_HOUSE);
    const int rent_hotel = static_cast<int>(EnumType::RENT_HOTEL);

private:
    int status;
    std::shared_ptr<Player> owner;
    std::string coordinates;
};

template <typename EnumType>
std::ostream &operator<<(std::ostream &os, const Tile<EnumType> &t);

#include "../src/Tile.hpp"

#endif
