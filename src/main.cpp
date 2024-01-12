/*
 *  Authors: Niccolò Pasetto
 */

#include <iostream>
#include <string>
#include <memory>

#include "../include/Player.h"
#include "../include/Tile.h"
#include "../include/Constants.h"
#include "../include/GameBoard.h"
#include "../include/Robot.h"
#include "../include/Logger.h"

using namespace std;

/*
 * ----------------------------- Main -------------------------------
 * TODO: Controlli sulla vittoria
 *
 * ------------------------------------------------------------------
 */

void play(GameBoard &gameBoard)
{
    const unsigned int MAX_TURNS = 1000;
    unsigned int turn_number = 0;
    // Ciclo principale del gioco, si ripete finchè
    // ci sono giocatori in gioco e finchè non viene
    // superato il limite di turni
    while(!gameBoard.is_game_finished() && turn_number <= MAX_TURNS)
    {
        cout<< "\nTurno "<<++turn_number<<endl;
        gameBoard.next_turn();
    }

    if(turn_number >= MAX_TURNS)
    {
        cout<<"\nPartita terminata, superato numero turni massimo!\n";
        // Stampa ordine giocatori per fiorini
        // Vince il piu' ricco
    }
    // Stampare chi ha vinto e passare il messaggio al logger
    cout<<"Gioco finito! Qualcuno ha vinto\n";

    return;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // Definisce il tipo di partita
    //      true    4 computers
    //      false   1 giocatore e 3 computers
    bool gameType = false;
    Logger logger;

    if(argc < 2)
    {
        cout<<"[!] Numero di argomenti passati da terminale insufficienti\n";
        cout<<"Esempi:\n\t$ ./monopoly human";
        cout<<"\n\t$ ./monopoly\n";
        return -1;
    }
    else if(argc > 2)
    {
        cout<<"[!] Troppi argomenti passati da terminale\n";
        cout<<"Esempi:\n\t$ ./monopoly human";
        cout<<"\n\t$ ./monopoly computer\n";
        return -1;
    }
    else
    {
        char *str = argv[1];
        string arg = "";
        int i = 0;
        while(str[i] != '\0')
            arg += tolower(str[i++]);

        if(arg == "computer")
            gameType = true;
        else if(arg == "human")
            gameType = false;
        else
        {
            cout<<"[!] Argomento passato da terminale invalido\n";
            cout<<"Esempi:\n\t$ ./monopoly human";
            cout<<"\n\t$ ./monopoly computer\n";
            return -1;
        }
    }

    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
    shared_ptr<Player> p3;
    shared_ptr<Player> p4;

    if(gameType)
    {
        p1 = make_shared<Robot>();
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }
    else
    {
        string name;
		bool ask = false;
		while(!ask)
        {
            cout<<"Inserisci nome giocatore umano:\n>>> ";
            cin>>name;
			if(name.length() <= 2)
				cout<<"\nNome troppo corto!\n\n";
			else if(name.length() >= 20)
				cout<<"\nNome troppo lungo!\n\n";
			else if(name == "LucaTonin" || name == "ltonin")
			{
				ask = true;
				cout<<"\nBenvenuto prof, ha già vinto\n";
			}
			else
				ask = true;
        }
		while(name.length() < 2 || name.length() > 10);

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