/*
 *  Authors: Leonardo Mosele & Nicolò Pasetto & Davide Saladino
 */

#include <iostream>
#include <string>
#include <memory>
#include "Player/Player.h"
#include "Tile/Tile.h"
#include "Constants.h"
#include "GameBoard/GameBoard.h"
#include "Player/Robot.h"
using namespace std;

/*
 * ----------------------------- Main -------------------------------
 * TODO: - 
 * ------------------------------------------------------------------
 */

void menu(void)
{

}

void play(GameBoard& gameBoard, shared_ptr<Player> p1, shared_ptr<Player> p2, shared_ptr<Player> p3, shared_ptr<Player> p4)
{
    int turn = 0;
    while (!gameBoard.gameFinished)
    {
        switch(turn % 4)
        {
            case 0:
                menu();
                break;
            case 1:
                menu();
                break;
            case 2:
                menu();
                break;
            case 3:
                menu();
                break;
        }

        turn++;
    }

    return;
}

int main(int argc, char* argv[])
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
        char* str = argv[1];
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
            cout<<"Inserisci nome giocatore umano:\n>>>";
            cin>>name;
        } while (name.length() < 2 || name.length() > 10);
        p1 = make_shared<Player>(name);
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }

    play(gameBoard, p1, p2, p3, p4);

    return 0;
}