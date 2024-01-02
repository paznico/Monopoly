/*
 * Author: Davide Saladino
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "Tile.h"

/*
* ----------------------- Tile implementation -----------------------
* TODO: - check (and complete) the constructors
        - once the above is done, finish the game mechanics (buy, build, etc.)
* -------------------------------------------------------------------
*/

/* Constructors */
template <typename EnumType>
Tile<EnumType>::Tile() : status(0), owner(nullptr) {} // Default

template <typename EnumType>
Tile<EnumType>::Tile(const Tile &t) : status(t.status), owner(t.owner) {} // Copy

template <typename EnumType>
Tile<EnumType>::Tile(Tile &&t) : status(t.status), owner(t.owner)
{
    t.status = 0;
    t.owner = nullptr;
}

/* Operators overloading */
template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(const Tile &t) // Copy
{
    this->status = t.status;
    this->owner = t.owner;
    return *this;
}

template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(Tile &&t) // Move
{
    this->status = t.status;
    this->owner = t.owner;
    t.status = 0;
    t.owner = nullptr;
    return *this;
}

/* Getters */
template <typename EnumType>
unsigned int Tile<EnumType>::get_status(void) const
{
    return this->status;
}

template <typename EnumType>
std::shared_ptr<Player> Tile<EnumType>::get_owner(void) const
{
    return owner;
}

/* Game mechanics */
template <typename EnumType>
void Tile<EnumType>::buy_terrain(std::shared_ptr<Player> p)
{
    if (status == 0 && p->get_balance() >= cost_property)
    {
        owner = p;
        int new_balance = owner->get_balance() - cost_property;
        owner->set_balance(new_balance);
        status++;

        // Prints some debugging info (owner's balance and name)
        std::cout << owner->get_name() << " bought a " << get_type() << " tile!" << std::endl;
        std::cout << "\t" << owner << std::endl;
    }
    else
        std::cout << p->get_name() << ", you can't build on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_house(std::shared_ptr<Player> p)
{
    if (!owner)
    {
        std::cout << "This tile has yet to be purchased!!\n";
        return;
    }

    if (status == 1 && p == owner && p->get_balance() >= cost_house)
    {
        int new_balance = owner->get_balance() - cost_house;
        owner->set_balance(new_balance);
        status++;
        std::cout << owner->get_name() << " built a house on a " << get_type() << " tile!\n";
        std::cout << "\t" << owner << std::endl;
    }
    else
        std::cout << p->get_name() << ", you can't build a house on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_hotel(std::shared_ptr<Player> p)
{
    std::cout << "You can't build hotels on this tile.\n";
}

template <typename EnumType>
void Tile<EnumType>::reset(void)
{
    std::cout << "You can't reset an angular tile!\n";
}

/* Utility Methods */
template <typename EnumType>
std::string Tile<EnumType>::get_type(void) const
{
    std::string tileType = typeid(EnumType).name();

    if (tileType.find("Cheap") != std::string::npos)
        tileType = "cheap";
    else if (tileType.find("Standard") != std::string::npos)
        tileType = "standard";
    else if (tileType.find("Luxury") != std::string::npos)
        tileType = "luxury";
    else
        tileType = "angular";

    return tileType;
}

/* Operator overloading */
template <typename EnumType>
std::ostream &operator<<(std::ostream &os, const Tile<EnumType> &t)
{
    return os << t.get_type() << " tile: " << t.get_status() << " " << t.get_owner() << "\n";
}

#endif
