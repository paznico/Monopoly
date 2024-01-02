/*
 *  Author: Leonardo Mosele e Davide Saladino
 */

#include "Player.h"

Player::Player(void)
{
    this->balance = 100;
    this->name = "";
}

Player::Player(std::string n)
{
    this->balance = 100;
    this->name = n;
}

/*
Player::Player(const Player &p)
{
    this->balance = p.balance;
    this->name = p.name;
}
*/

Player::Player(Player &&p)
{
    this->balance = p.balance;
    this->name = p.name;
    p.name.clear();
    p.balance = 0;
}

// ?
Player::~Player()
{
    this->balance = 0;
    this->name = "";
}
// ?

/*
Player &Player::operator=(const Player &p)
{
    this->balance = p.balance;
    this->name = p.name;
    return *this;
}
*/

Player &Player::operator=(Player &&p)
{
    this->balance = p.balance;
    this->name = p.name;
    p.balance = 0;
    p.name.clear();
    return *this;
}

unsigned int Player::get_balance(void) const
{
    return this->balance;
}

std::string Player::get_name(void) const
{
    return this->name;
}

void Player::set_balance(int new_balance)
{
    if (new_balance <= 0)
        return;
    else
        this->balance = new_balance;
}

unsigned int Player::dice_throw(void) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    return dist6(rng) + dist6(rng);
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    return os << p.get_name() << " has " << p.get_balance() << " fiorini\n";
}

bool operator==(const Player &p1, const Player &p2)
{
    return p1.get_name() == p2.get_name();
}

bool operator!=(const Player &p1, const Player &p2)
{
    return p1.get_name() != p2.get_name();
}
