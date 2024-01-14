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
 * slicing issues inherent with polymorphism. Tile generation occurs
 * in the constructor through the generate_tiles() method. The show()
 * method is then utilized to display the game board on the screen.
 * -------------------------------------------------------------------
 */

/*
	Siccome usiamo gli unique_ptr su tiles non possiamo farne la copia!
	Ho disabilitato copia/spostamento, controllare anche voi
	Secondo me lo spostamento bisogna farlo però non saprei come
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

    /* Functions */
    void find_unique(std::vector<int> pos, std::multimap<int, std::shared_ptr<Player>> players, std::vector<std::shared_ptr<Player>>& vec);
    void generate_tiles(void);
    bool is_game_finished(void) const { return this->gameFinished; };

    void next_turn(void);

    int dice_throw(void) const;
    void action_handler(std::shared_ptr<Player>);
    void show(void);
    void show_holdings(void);
	void get_results(void) const;
};

#endif
