/*
* Author: Davide Saladino
*/
#ifndef TILE_HPP
#define TILE_HPP

#include "Tile.h"

/*
* ----------------------- Tile implementation -----------------------
* TODO: - check (and complete) the constructors
*       - figure out discrepancies between the Player shared 
          pointer and the Player reference
        - once the above is done, finish the game mechanics (buy, build, etc.)
* -------------------------------------------------------------------
*/

/* Constructors */
template <typename EnumType>
Tile<EnumType>::Tile() : status(0), owner(nullptr) {}                               // Default

template <typename EnumType>
Tile<EnumType>::Tile(const Tile &t) : status(t.status), owner(t.owner) {}           // Copy

template <typename EnumType>
Tile<EnumType>::Tile(Tile &&t) : status(t.status), owner(t.owner)                   // Move
{
    t.status = 0;
    t.owner.reset();
}

/* Operators overloading */
template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(const Tile &t)                            // Copy
{
    this->status = t.status;
    this->owner = t.owner;
    return *this;
}

template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(Tile &&t)                                 // Move
{
    this->status = t.status;
    this->owner = t.owner;
    t.status = 0;
    t.owner.reset();
    return *this;
}

/* Getters */
template <typename EnumType>
unsigned int Tile<EnumType>::get_status(void) const
{
    return this->status;
}

template <typename EnumType>
Player &Tile<EnumType>::get_owner(void) const
{
    if (this->owner)
    {
        return *(this->owner);
    }
    else
    {
        throw std::logic_error("Attempt to get owner from a Tile with nullptr owner.");
    }
}

/* Game mechanics */
template <typename EnumType>
void Tile<EnumType>::buy_terrain(std::shared_ptr<Player> p)
{
    if (this->status == 0 && p->get_balance() >= this->cost_property)
    {
        this->owner = p;
        int new_balance = this->owner->get_balance() - this->cost_property;
        this->owner->set_balance(new_balance);
        this->status++;

        // Prints some debugging info (owner's balance and name)
        std::cout << this->owner->get_name() << " bought a " << this->get_type() << " tile!" << std::endl;
        std::cout << "\t" << *(this->owner.get()) << std::endl;
    }
    else
        std::cout << this->owner->get_name() << ", you can't build a house on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_house(Player &p)
{
    if (this->status == 1 && p == *(this->owner) && p.get_balance() >= this->cost_house)
    {
        int new_balance = this->owner->get_balance() - this->cost_house;
        this->owner->set_balance(new_balance);
        this->status++;
        std::cout << this->owner->get_name() << " built a house on a " << this->get_type() << " tile!\n";
        std::cout << "\t" << *(this->owner.get()) << std::endl;
    }
    else
        std::cout << this->owner->get_name() << ", you can't build a house on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_hotel(Player &p)
{
    std::cout << "Non puoi costruire hotels su questa casella mona\n";
}

template <typename EnumType>
void Tile<EnumType>::reset(void)
{
    std::cout << "Non puoi resettare una casella angolare!\n";
}

/* Utility Methods */
template <typename EnumType>
std::string Tile<EnumType>::get_type(void) const
{
    std::string tileType = typeid(EnumType).name();

    if(tileType.find("Cheap") != std::string::npos) tileType = "cheap";
    else if(tileType.find("Standard") != std::string::npos) tileType = "standard";
    else if (tileType.find("Luxury") != std::string::npos) tileType = "luxury";
    else tileType = "angular";

    return tileType;
}

/* Operator overloading */
template <typename EnumType>
std::ostream &operator<<(std::ostream &os, const Tile<EnumType> &t)
{
    return os << t.get_type() << " tile: " << t.get_status() << " " << t.get_owner() << "\n";
}

#endif