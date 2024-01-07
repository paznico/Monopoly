/*
 *  Author: Niccolò Pasetto
 */

#include "../include/Player.h"

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

Player::Player(Player &&p)
{
    this->balance = p.balance;
    this->name = p.name;
    p.name.clear();
    p.balance = 0;
}

Player::~Player()
{
    this->balance = 0;
    this->name = "";
}

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

int Player::get_position(void)
{
    return this->position;
}

void Player::set_balance(int new_balance)
{
    if (new_balance <= 0)
        return;
    else
        this->balance = new_balance;
}

void Player::increment_player_pos(const int pos)
{
    this->position += (pos % 28);
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    return os << p.get_name() << " has " << p.get_balance() << " fiorini\n";
}