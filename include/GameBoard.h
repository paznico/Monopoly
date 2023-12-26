#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include "Tile.h"

class GameBoard
{
    public:
        // std::vector<Tile> tiles;         THIS OR THE NEXT ONE PAZ???????????????!
        // Tile gameboard[28];

    private:
        /* Constructor */
        GameBoard(void);                    // default 
        GameBoard(GameBoard&);              // copy
        GameBoard(GameBoard&&);             // move

        void show(void);
};

#endif