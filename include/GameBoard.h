#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Tile.h"

class GameBoard
{
    public:
        std::vector<Tile> tiles;

    private:
        /* Constructor */
        GameBoard(void);                    // default 
        GameBoard(GameBoard&);              // copy
        GameBoard(GameBoard&&);             // move

        void show(void);
};

#endif