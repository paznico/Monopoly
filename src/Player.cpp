/*
 *  Author: Pasetto Niccolò
 */

#include "../include/Player.h"

Player::Player(void)
{
    this->balance = this->initial_balance;
    this->name = "";
    this->position = 0;
}

Player::Player(std::string n)
{
    this->balance = this->initial_balance;
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

int Player::get_balance(void) const
{
    return this->balance;
}

std::string Player::get_name(void) const
{
    return this->name;
}

int Player::get_position(void) const
{
    return this->position;
}

void Player::set_balance(int new_balance)
{
    if(new_balance < 0)
        return;
    else
        this->balance = new_balance;
}

void Player::move(const unsigned int pos)
{
    this->position = (this->position + pos) % 28;
}

unsigned int Player::make_choice(void) const
{
	std::string choice = " ";
	std::cin>>choice;
	if(choice.at(0) == 'M')
		return 2;
	else if(choice.at(0) == 'S')
		return 1;
	else
		return 0;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    return os<<p.get_name()<<" ha "<<p.get_balance()<<" fiorini\n";
}
