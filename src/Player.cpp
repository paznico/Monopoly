#include "Player.h"

Player::Player(void)
{
    this->balance = 100;
    this->nome = "";
}

Player::Player(std::string n)
{
    this->balance = 100;
    this->nome = n;
}

Player::Player(const Player &p)
{
    this->balance = p.balance;
    this->nome = p.nome;
}

Player::Player(Player &&p)
{
    this->balance = p.balance;
    this->nome = p.nome;
    p.nome.clear();
    p.balance = 0;
}

// ?
Player::~Player()
{
    this->balance = 0;
    this->nome = "";
}
// ?

Player &Player::operator=(const Player &p)
{
    this->balance = p.balance;
    this->nome = p.nome;
    return *this;
}

Player &Player::operator=(Player &&p)
{
    this->balance = p.balance;
    this->nome = p.nome;
    p.balance = 0;
    p.nome.clear();
    return *this;
}

unsigned int Player::get_balance(void) const
{
    return this->balance;
}

std::string Player::get_name(void) const
{
    return this->nome;
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
    // Return number between 0 and 12
    return (rand() % 13);
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
    return os << p.get_name() << " possiede " << p.get_balance() << " fiorini\n";
}

bool operator==(const Player &p1, const Player &p2)
{
    return p1.get_name() == p2.get_name();
}

bool operator!=(const Player &p1, const Player &p2)
{
    return p1.get_name() != p2.get_name();
}
