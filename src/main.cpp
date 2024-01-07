/*
 *  Authors: Leonardo Mosele & Nicolò Pasetto & Davide Saladino
 */

#include <iostream>
#include <string>
#include <memory>

#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/Constants.h"
#include "../include/GameBoard.h"
#include "../include/Robot.h"
using namespace std;

/*
 * ----------------------------- Main -------------------------------
 * TODO: -
 *
 * ------------------------------------------------------------------
 */

void play(GameBoard &gameBoard, shared_ptr<Player> p1, shared_ptr<Player> p2, shared_ptr<Player> p3, shared_ptr<Player> p4)
{
    // Run the game until one of the players
    // has won (or max turns are reached)
    while (!gameBoard.is_game_finished())
    {

        int currentPlayer = gameBoard.current_player(); // Get the current player using the turn number
        int dice_num = gameBoard.dice_throw();          // Throw the dice

        gameBoard.increment_player_pos(currentPlayer, dice_num);
        // Move the player and perform the action
        // related to the square it is in.
        if (currentPlayer == 0)
            gameBoard.action_handler(p1);
        else if (currentPlayer == 1)
            gameBoard.action_handler(p2);
        else if (currentPlayer == 2)
            gameBoard.action_handler(p3);
        else if (currentPlayer == 3)
            gameBoard.action_handler(p4);

        gameBoard.increment_turn(); // Increment the turn number
    }

    cout << "Game finished!\n";

    return;
}

int main(int argc, char *argv[])
{

    // Defines the game type:
    //      true    4 computers
    //      false   1 player and 3 computers
    bool gameType = false;

    if (argc < 2)
    {
        cout << "[!] Insufficient command-line arguments provided\n";
        cout << "Example:\n\t$ ./executable_name human";
        cout << "\n\t$ ./executable_name computer\n";
        return -1;
    }
    else if (argc > 2)
    {
        cout << "[!] Too many command-line arguments passed\n";
        cout << "Examples:\n\t$ ./executable_name human";
        cout << "\n\t$ ./executable_name computer\n";
        return -1;
    }
    else
    {
        char *str = argv[1];
        string arg = "";
        int i = 0;
        while (str[i] != '\0')
            arg += tolower(str[i++]);

        if (arg == "computer")
            gameType = true;
        else if (arg == "human")
            gameType = false;
        else
        {
            cout << "[!] Invalid command-line argument\n";
            cout << "Examples:\n\t$ ./executable_name human";
            cout << "\n\t$ ./executable_name computer\n";
            return -1;
        }
    }

    GameBoard gameBoard = GameBoard();
    gameBoard.show();

    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
    shared_ptr<Player> p3;
    shared_ptr<Player> p4;

    if (gameType)
    {
        p1 = make_shared<Robot>();
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }
    else
    {
        string name;
        do
        {
            cout << "Inserisci nome giocatore umano:\n>>>";
            cin >> name;
        } while (name.length() < 2 || name.length() > 10);
        p1 = make_shared<Player>(name);
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }

    play(gameBoard, p1, p2, p3, p4);

    return 0;
}