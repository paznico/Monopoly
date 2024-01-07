/*
 * Autore file: Davide Saladino
 */
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Tile.h"
#include "BaseTile.h"
#include "Player.h"
#include "Constants.h"

#include <vector>
#include <memory>

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
    std::vector<int> playersPos = std::vector<int>(4, 0);
    bool gameFinished = false;
    unsigned int turn = 0;
public:
    std::vector<std::unique_ptr<BaseTile>> tiles = std::vector<std::unique_ptr<BaseTile>>(28);   // temporarily public for testing purposes!

    GameBoard(void);
    GameBoard(GameBoard &);
    GameBoard(GameBoard &&);

    void generate_tiles(void);
    bool is_game_finished(void) { return this->gameFinished; };

    int get_turn(void) const { return this->turn; };
    void increment_turn(void) { this->turn++; };
    int current_player(void) const { return this->turn % 4; };

    int dice_throw(void) const;
    void action_handler(std::shared_ptr<Player>);
    void increment_player_pos(const int, const int);
    void show(void);
};

#endif