/*
 * Author: Davide Saladino
 */
#ifndef TILE_HPP
#define TILE_HPP

#include "../include/Tile.h"

/*
* ----------------------- Tile implementation -----------------------
* TODO:
        - Controllare logica funzioni di acquisto e pernottamento
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
	if(get_type() == " ")
        std::cout << p->get_name() << ", non puoi costruire su una casella angolare!\n";
	else if(status != 0)
		std::cout<<p->get_name() << ", non puoi costruire su questa casella!\n";
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
    if(!owner)
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
	else if(status != 1)
        std::cout << p->get_name() << ", non puoi costruire una casa su questo terreno!\n";
	else if(p != owner)
        std::cout << p->get_name() << ", non puoi costruire una casa sul terreno di un altro giocatore!\n";
    else if(p->get_balance() >= cost_house)
    {
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
    if(!owner)
        std::cout << "Questo terreno deve ancora essere acquistato!!\n";
	else if(status != 2)
        std::cout << p->get_name() << ", non puoi costruire un albergo su questo terreno!\n";
	else if(p != owner)
        std::cout << p->get_name() << ", non puoi costruire un albergo sul terreno di un altro giocatore!\n";
    else if(p->get_balance() >= cost_hotel)
    {
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
    if(status == 2 && p != owner)
    {
        // If player can't pay rent
        if(p->get_balance() <= this->rent_house) {
            // Give all his remaining money to the owner
            owner->set_balance(owner->get_balance() + p->get_balance());
            p->set_balance(p->get_balance() - this->rent_house);

            std::string str = p->get_name() + " e' stato eliminato!";
			// AGGIUNGERE ELIMINAZIONE
            std::cout << str << std::endl;
            Logger::get_instance().log(str);
            return;
        }
        
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
    if(status == 3 && p != owner)
    {
        if(p->get_balance() <= this->rent_hotel) {
            std::string str = p->get_name() + " e' stato eliminato!";
            std::cout << str << std::endl;
			// AGGIUNGERE ELIMINAZIONE
            Logger::get_instance().log(str);
            return;
        }
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
