/*
 *  Authors: Leonardo Mosele & Niccolò Pasetto & Davide Saladino
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

void play(GameBoard &gameBoard)
{
    // Run the game until one of the players
    // has won (or max turns are reached)
    int i = 0;
    while (!gameBoard.is_game_finished())
    {
        cout << "Turno " << ++i << endl;
        gameBoard.next_turn();
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

    GameBoard gameBoard = GameBoard(p1, p2, p3, p4);
    gameBoard.show();

    play(gameBoard);

    return 0;
}