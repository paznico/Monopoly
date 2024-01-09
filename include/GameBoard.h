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
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <queue>
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

class GameBoard
{
private:
    std::queue<std::shared_ptr<Player>> players;
    std::vector<std::unique_ptr<BaseTile>> tiles = std::vector<std::unique_ptr<BaseTile>>(28);
    bool gameFinished = false;
    
public:

    GameBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Player> p3, std::shared_ptr<Player> p4);
    GameBoard(GameBoard &);
    GameBoard(GameBoard &&);


    void find_unique(std::vector<int> pos, std::multimap<int, std::shared_ptr<Player>> players, std::vector<std::shared_ptr<Player>>& vec);
    void generate_tiles(void);
    bool is_game_finished(void) const { return this->gameFinished; };

    void next_turn(void);

    int dice_throw(void) const;
    void action_handler(std::shared_ptr<Player>);
    void show(void);
    void show_property(void);
};

#endif