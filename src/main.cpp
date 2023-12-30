#include <iostream>
#include "Player/Player.h"
#include "Tile/Tile.h"
#include "Constants.h"
#include "GameBoard/GameBoard.h"
using namespace std;

int main() {
    GameBoard gameBoard = GameBoard();
    Player player1 = Player("Davide");  // ptr1
    Player player2 = Player("Giovanni");

    std::shared_ptr<Player> p1 = std::make_shared<Player>(player1);
    Tile<CheapTile> tile1 = Tile<CheapTile>();

    tile1.buy_terrain(p1);

    std::cout << p1->get_balance();

    // for (const auto& tile : gameBoard.tiles) {
    //     tile->buy_terrain(player1);
    // }

    //gameBoard.show();

    return 0;
}
