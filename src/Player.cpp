/*
 *  Author: Niccolò Pasetto
 */

#include "../include/Player.h"

Player::Player(void)
{
    this->balance = 100;
    this->name = "";
    this->position = 0;
}

Player::Player(std::string n)
{
    this->balance = 100;
    this->name = n;
    this->position = 0;
}

Player::Player(Player &&p)
{
    this->balance = p.balance;
    this->name = p.name;
    this->position = p.position;
    p.name.clear();
    p.balance = 0;
}

Player::~Player()
{
    this->balance = 0;
    this->name = "";
    this->position = 0;
}

Player &Player::operator=(Player &&p)
{
    this->balance = p.balance;
    this->name = p.name;
    this->position = p.position;
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

void Player::add_balance(unsigned int amount)
{
    this->balance += amount;
}

bool Player::sub_balance(unsigned int amount)
{
    if(this->balance < amount)
        return false;
    else
        this->balance -= amount;
    
    return true;
}

void Player::set_balance(int new_balance)
{
    if(new_balance <= 0)
        return;
    else
        this->balance = new_balance;
}

void Player::move(const unsigned int pos)
{
    this->position = (this->position + pos) % 28;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    return os<<p.get_name()<<" ha "<<p.get_balance()<<" fiorini\n";
}