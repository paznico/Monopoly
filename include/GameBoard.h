/*
 * Autore file: Davide Saladino
 */
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include "BaseTile.h"
#include "Player.h"
#include "Constants.h"

#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <deque>
#include <map>

/*
 * ------------------------- GameBoard class -------------------------
 * A class representing the game board. Tiles are stored in a
 * vector of unique pointers to BaseTile objects, enabling a diverse
 * collection of tile types. The use of unique pointers ensures
 * effective memory management, preventing memory leaks and avoiding
 * slicing issues inherent with polymorphism. Players are stored in a
 * deque of shared pointers to Player objects, allowing for efficient
 * insertion and deletion of players from the game. The deque also allows
 * for easy iteration through the players in the game, as well as
 * random access to players. 
 * -------------------------------------------------------------------
 */

class GameBoard
{
private:
    std::deque<std::shared_ptr<Player>> players;
    std::vector<std::unique_ptr<BaseTile>> tiles = std::vector<std::unique_ptr<BaseTile>>(28);
    bool gameFinished = false;
    
public:

    /* Constructor */
    GameBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Player> p3, std::shared_ptr<Player> p4);
	GameBoard(const GameBoard&) = delete;
    GameBoard(GameBoard &&);

	/* Operators overloading */
	GameBoard& operator=(const GameBoard&) = delete;
	GameBoard& operator=(GameBoard&&);

    /* Member Functions */
    void find_unique(std::vector<int> pos, std::multimap<int, std::shared_ptr<Player>> players, std::vector<std::shared_ptr<Player>>& vec);
    void generate_tiles(void);
    bool is_game_finished(void) const { return this->gameFinished; };

    void next_turn(void);
    void action_handler(std::shared_ptr<Player>);
    void show(void);
    void show_holdings(void);

    int dice_throw(void) const;
	void get_results(void) const;
};

#endif
