/*
 * Author: Davide Saladino
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "../include/Tile.h"

/*
* ----------------------- Tile implementation -----------------------
* -------------------------------------------------------------------
*/

/* Constructors */
template <typename EnumType>
Tile<EnumType>::Tile() : status(0), owner(nullptr), coordinates("") {}      // Default

template <typename EnumType>
Tile<EnumType>::Tile(const std::string& coordinates)
{
    this->coordinates = coordinates;
    this->status = 0;
    this->owner = nullptr;
}

template <typename EnumType>
Tile<EnumType>::Tile(const Tile &t) : status(t.status), owner(t.owner) {}   // Copy

template <typename EnumType>
Tile<EnumType>::Tile(Tile &&t) : status(t.status), owner(t.owner)           // Move
{
    t.status = 0;
    t.owner = nullptr;
}

/* Operators overloading */
template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(const Tile &t)                    // Copy
{
    this->status = t.status;
    this->owner = t.owner;
    return *this;
}

template <typename EnumType>
Tile<EnumType> &Tile<EnumType>::operator=(Tile &&t)                         // Move
{
    this->status = t.status;
    this->owner = t.owner;
    t.status = 0;
    t.owner = nullptr;
    return *this;
}

/* Getters */
// Get the status of the tile ( 0 = free, 1 = owned, 2 = house, 3 = hotel )
template <typename EnumType>
unsigned int Tile<EnumType>::get_status(void) const
{
    return this->status;
}

// Return the owner of the tile
template <typename EnumType>
std::shared_ptr<Player> Tile<EnumType>::get_owner(void) const
{
    return owner;
}

/* Game mechanics */
template <typename EnumType>
void Tile<EnumType>::buy_terrain(std::shared_ptr<Player> p)
{
    // If angular tile, the player can't buy it
	if(get_type() == " ")
        std::cout << p->get_name() << ", non puoi costruire su una casella angolare!\n";
    // If the tile is not free, the player can't buy it
	else if(status != 0)
		std::cout<<p->get_name() << ", non puoi costruire su questa casella!\n";
    // If the player has enough money, he can buy the tile
    else if(p->get_balance() >= cost_property)
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
        std::cout << p->get_name() << ", non hai abbastanza fiorini per comprare questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_house(std::shared_ptr<Player> p)
{
    // If the tile is not owned, the player can't build a house
    if(!owner)
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
    // If the tile is not owned, the player can't build a house
	else if(status != 1)
        std::cout << p->get_name() << ", non puoi costruire una casa su questo terreno!\n";
    // If the player is not the owner, he can't build a house
	else if(p != owner)
        std::cout << p->get_name() << ", non puoi costruire una casa sul terreno di un altro giocatore!\n";
    // If the player has enough money, he can build a house
    else if(p->get_balance() >= cost_house)
    {
        // Set the new balance for the owner 
        // and update the status of the tile
        int new_balance = owner->get_balance() - cost_house;
        owner->set_balance(new_balance);
        status++;

        std::string str = owner->get_name() + " ha costruito una casa sul terreno " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non hai abbastanza fiorini per costruire una casa su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::build_hotel(std::shared_ptr<Player> p)
{
    // If the tile is not owned, the player can't build a hotel
    if(!owner)
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
    // If the tile is not owned, the player can't build a hotel
	else if(status != 2)
        std::cout << p->get_name() << ", non puoi costruire un albergo su questo terreno!\n";
    // If the player is not the owner, he can't build a hotel
	else if(p != owner)
        std::cout << p->get_name() << ", non puoi costruire un albergo sul terreno di un altro giocatore!\n";
    // If the player has enough money, he can build a hotel
    else if(p->get_balance() >= cost_hotel)
    {
        // Set the new balance for the owner 
        // and update the status of the tile
        int new_balance = owner->get_balance() - cost_hotel;
        owner->set_balance(new_balance);
        status++;

        std::string str = owner->get_name() + " ha costruito un albergo sul terreno " + get_coord();
        Logger::get_instance().log(str);
        std::cout << str << std::endl;
    }
    else
        std::cout << p->get_name() << ", non hai abbastanza fiorini per costruire un albergo su questo terreno!\n";
}

template <typename EnumType>
void Tile<EnumType>::pay_rent_house(std::shared_ptr<Player> p)
{
    // If the player is not the owner and the tile 
    // has a house, the player must pay the rent
    if(status == 2 && p != owner)
    {
        // If player can't pay rent
        if(p->get_balance() <= this->rent_house) {
            // Give all his remaining money to the owner of the tile
            owner->set_balance(owner->get_balance() + p->get_balance());
            p->set_balance(p->get_balance() - this->rent_house);

            std::string str = p->get_name() + " e' stato eliminato!";
            std::cout << str << std::endl;
            Logger::get_instance().log(str);
            return;
        }
        
        // Set the new balance for the player and the owner
        p->set_balance(p->get_balance() - this->rent_house);
        owner->set_balance(owner->get_balance() + this->rent_house);

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
    // If the player is not the owner and the tile 
    // has an hotel, the player must pay the rent
    if(status == 3 && p != owner)
    {
        if(p->get_balance() <= this->rent_hotel) {
            std::string str = p->get_name() + " e' stato eliminato!";
            std::cout << str << std::endl;
            Logger::get_instance().log(str);
            return;
        }

        // Set the new balance for the player and the owner
        p->set_balance(p->get_balance() - this->rent_hotel);
        owner->set_balance(owner->get_balance() + this->rent_hotel);

        std::string str = p->get_name() + " ha pagato " + std::to_string(this->rent_hotel) + " fiorini a " + owner->get_name() +
         " per pernottamento nella casella " + get_coord();
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

// Return the type of the tile (cheap, standard, luxury)
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
