#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "../Tile/Tile.h"
#include "../Tile/BaseTile.h"
#include "../Player/Player.h"
#include "../Constants.h"

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
public:
    std::vector<std::unique_ptr<BaseTile>> tiles = std::vector<std::unique_ptr<BaseTile>>(28);   // temporarily public for testing purposes!

    GameBoard(void);
    GameBoard(GameBoard &);
    GameBoard(GameBoard &&);

    void generate_tiles(void);
    void show(void);
};

#endif