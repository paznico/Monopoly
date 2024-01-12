/*
 * Author: Davide Saladino
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "../include/Tile.h"
#include "../include/Logger.h"

/*
* ----------------------- Tile implementation -----------------------
* TODO: - check (and complete) the constructors
        - fix cout on game mechanics
        - if player lose, remove him from the game (make stack for players)
* -------------------------------------------------------------------
*/

/* Constructors */
template <typename EnumType>
Tile<EnumType>::Tile() : status(0), owner(nullptr), coordinates("") {} // Default

template <typename EnumType>
Tile<EnumType>::Tile(const std::string& coordinates)
{
    this->coordinates = coordinates;
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
    if (status == 0 && p->get_balance() >= cost_property && get_type() != " ")
    {
        owner = p;
        int new_balance = owner->get_balance() - cost_property;
        owner->set_balance(new_balance);
        status++;

        // Prints some debugging info (owner's balance and name)
        std::string str = owner->get_name() + " ha acquistato il terreno " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non puoi costruire su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_house(std::shared_ptr<Player> p)
{
    if (!owner)
    {
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
        return;
    }

    if (status == 1 && p == owner && p->get_balance() >= cost_house)
    {
        int new_balance = owner->get_balance() - cost_house;
        owner->set_balance(new_balance);
        status++;

        std::string str = owner->get_name() + " ha costruito una casa sul terreno " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non puoi costruire una casa su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_hotel(std::shared_ptr<Player> p)
{
    if (!owner)
    {
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
        return;
    }

    if (status == 2 && p == owner && p->get_balance() >= cost_hotel)
    {
        int new_balance = owner->get_balance() - cost_hotel;
        owner->set_balance(new_balance);
        status++;

        std::string str = owner->get_name() + " ha migliorato una casa in albergo sul terreno " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non puoi costruire un hotel su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::pay_rent_house(std::shared_ptr<Player> p)
{
    if(status == 1 && p != owner)
    {
        if(p->get_balance() < this->rent_house) {
            std::string str = p->get_name() << " e' stato eliminato!";
            std::cout << str << std::endl;
            Logger::get_instance().log(str);
            return;
        }
        
        p->sub_balance(this->rent_house);
        owner->add_balance(this->rent_house);

        std::string str = p->get_name() + " ha pagato " + std::to_string(this->rent_house) + " a " + owner->get_name() +
         " per pernottamento nella casella " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non puoi pagare l'affitto su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::pay_rent_hotel(std::shared_ptr<Player> p)
{
    if(status == 1 && p != owner)
    {
        if(p->get_balance() < this->rent_hotel) {
            std::string str = p->get_name() << " e' stato eliminato!";
            std::cout << str << std::endl;
            Logger::get_instance().log(str);
            return;
        }
        p->sub_balance(this->rent_hotel);
        owner->add_balance(this->rent_hotel);

        std::string str = p->get_name() + " ha pagato " + std::to_string(this->rent_hotel) + " fiorini a " + owner->get_name() +
         "per pernottamento nella casella " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non puoi pagare l'affitto in questa casella!\n";
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
    return os << t.get_type() << " casella: " << t.get_status() << " " << t.get_owner() << "\n";
}

#endif
