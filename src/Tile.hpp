/*
 * Author: Davide Saladino
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "../include/Tile.h"

/*
* ----------------------- Tile implementation -----------------------
* TODO: - check (and complete) the constructors
        - fix cout on game mechanics
        - if player lose, remove him from the game (make stack for players)
* -------------------------------------------------------------------
*/

/* Constructors */
template <typename EnumType>
Tile<EnumType>::Tile() : status(0), owner(nullptr), coordinate(null) {} // Default

template <typename EnumType>
Tile<EnumType>::Tile(const std::string& coord)
{
    this->coordinate = coord;
    this->status = 0;
    this->owner = nullptr;
}

template <typename EnumType>
Tile<EnumType>::Tile(const Tile &t) : status(t.status), owner(t.owner) {} // Copy

template <typename EnumType>
Tile<EnumType>::Tile(Tile &&t) : status(t.status), owner(t.owner) // Move
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
    if (!owner)
    {
        std::cout << "This tile has yet to be purchased!!\n";
        return;
    }

    if (status == 2 && p == owner && p->get_balance() >= cost_hotel)
    {
        int new_balance = owner->get_balance() - cost_hotel;
        owner->set_balance(new_balance);
        status++;

        std::cout << owner->get_name() << " built an hotel on a " << get_type() << " tile!\n";
        std::cout << "\t" << owner << std::endl;
    }
    else
        std::cout << p->get_name() << ", you can't build an hotel on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::pay_rent_house(std::shared_ptr<Player> p)
{
    if(status == 1 && p != owner)
    {
        if(p->get_balance() < this->rent_house) {
            std::cout << p->get_name() << " is bankrupt!\n";
            return;
        }
        
        p->sub_balance(this->rent_house);
        owner->add_balance(this->rent_house);

        /*
        int new_balance = p->get_balance() - this->rent_house;
        p->set_balance(newbalance(this->rent_house);
        owner->add_balance);
        new_balance = owner->get_balance() + this->rent_house;
        owner->set_balance(new_balance);
        */

        std::cout << p->get_name() << " paid " << this->rent_house << " to " << owner->get_name() << std::endl;
        std::cout << "\t" << p << std::endl;
        std::cout << "\t" << owner << std::endl;
    }
    else
        std::cout << p->get_name() << ", you can't pay rent on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::pay_rent_hotel(std::shared_ptr<Player> p)
{
    if(status == 1 && p != owner)
    {
        if(p->get_balance() < this->rent_hotel) {
            std::cout << p->get_name() << " is bankrupt!\n";
            return;
        }
        p->sub_balance(this->rent_hotel);
        owner->add_balance(this->rent_hotel);

        std::cout << p->get_name() << " paid " << this->rent_hotel << " to " << owner->get_name() << std::endl;
        std::cout << "\t" << p << std::endl;
        std::cout << "\t" << owner << std::endl;
    }
    else
        std::cout << p->get_name() << ", you can't pay rent on this tile!\n";
}

template <typename EnumType>
void Tile<EnumType>::reset(void)
{
    status = 0;
    owner = nullptr;
}

/* Utility Methods */
template <typename EnumType>
std::string Tile<EnumType>::get_type(void) const
{
    std::string tileType = typeid(EnumType).name();

    if (tileType.find("Cheap") != std::string::npos)
        tileType = "economica";
    else if (tileType.find("Standard") != std::string::npos)
        tileType = "standard";
    else if (tileType.find("Luxury") != std::string::npos)
        tileType = "lussuosa";
    else
        tileType = " ";

    return tileType;
}

/* Operator overloading */
template <typename EnumType>
std::ostream &operator<<(std::ostream &os, const Tile<EnumType> &t)
{
    return os << t.get_type() << " tile: " << t.get_status() << " " << t.get_owner() << "\n";
}

#endif
