#include "../include/Tile.h"
#include "../include/StandardTile.h"
#include <iostream>

int main (void)
{

    StandardTile tile ();

    tile.set_status(1);

    std::cout << tile.get_status();
}