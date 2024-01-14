/*
 *  Autore: Niccolò Pasetto
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

// Funzione che dato il tabellone itera eseguendo i turni
// finchè non viene incontrata una condizione di vittoria
void play(GameBoard &gameBoard)
{
    // Imposta numero massimo di turni da giocare
    const unsigned int MAX_TURNS = 100;
    // Inizializza numero di turni giocati
    unsigned int turn_number = 0;
    // Ciclo principale del gioco, si ripete finchè
    // ci sono giocatori in gioco e finchè non viene
    // superato il limite di turni
    while(!gameBoard.is_game_finished() && turn_number <= MAX_TURNS)
    {
        // Chiama la funzione per eseguire un turno
        ++turn_number;
        std::string str = "\nTurno " + std::to_string(turn_number) + "\n";
        cout<<str;
        Logger::get_instance().log(str);
        gameBoard.next_turn();
    }
    
    // Se é stato raggiunto il limite di turni
    if(turn_number > MAX_TURNS)
    {
        // Stampa i risultati
		std::string str = "Partita terminata, superato numero turni massimo!";
    	Logger::get_instance().log(str);
		gameBoard.get_results();
        // In questo caso vince il giocatore(i) con più fiorini vince(ono)
    }

    return;
}

int main(int argc, char *argv[])
{
    // Inizializza un seed casuale per il generatore
    // di numeri casuali
    srand((unsigned int)time(NULL));

    // Definisce il tipo di partita
    //      true    4 computers
    //      false   1 giocatore e 3 computers
    bool gameType = false;
    // Inizializza l'istanza di Logger che verrà usata durante la partita
    Logger logger;

    // Controlli sui parametri passati da terminale
    if(argc < 2)
    {
        // Se sono troppo pochi stampa messaggio di errore ed esempio di utilizzo
        cout<<"[!] Numero di argomenti passati da terminale insufficienti\n";
        cout<<"Esempi:\n\t$ ./monopoly human";
        cout<<"\n\t$ ./monopoly\n";
        // Ed esce
        return -1;
    }
    else if(argc > 2)
    {
        // Se sono troppi stampa messaggio di errore ed esempio di utilizzo
        cout<<"[!] Troppi argomenti passati da terminale\n";
        cout<<"Esempi:\n\t$ ./monopoly human";
        cout<<"\n\t$ ./monopoly computer\n";
        // Ed esce
        return -1;
    }
    else
    {
        // Controlla se il parametro ha senso
        char *str = argv[1];
        string arg = "";
        int i = 0;
        // Converte la stringa del parametro in lowercase
        // per controllarla in modo migliore
        while(str[i] != '\0')
            arg += tolower(str[i++]);

        // Imposta il tipo di partita se corrisponde
        if(arg == "computer")
            gameType = true;
        else if(arg == "human")
            gameType = false;
        else
        {
            // Se non corrisponde a un tipo di partita
            // stampa errore, esempio, esci
            cout<<"[!] Argomento passato da terminale invalido\n";
            cout<<"Esempi:\n\t$ ./monopoly human";
            cout<<"\n\t$ ./monopoly computer\n";
            return -1;
        }
    }

    // Inizializza shared_ptr per maneggiare i giocatori durante la partita
    // Vengono usati gli shared_ptr per evitare memory leak, dangling pinters,
    // doppie eliminazioni di aree di memoria e per nascondere l'utilizzo dei
    // puntatori. Inoltre diversi oggetti possono puntare ad un giocatore,
    // rendendo gli unique_ptr più difficili da utilizzare
    shared_ptr<Player> p1;
    shared_ptr<Player> p2;
    shared_ptr<Player> p3;
    shared_ptr<Player> p4;

    // In base al tipo di partita imposta
    if(gameType)
    {
        // 4 robot
        p1 = make_shared<Robot>();
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }
    else
    {
        // Chiedi nome al giocatore
        // Il nome deve essere compreso tra 2 e 20 caratteri
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
			else
				ask = true;
        }
		while(name.length() < 2 || name.length() > 10);

        // 1 giocatore e 3 robot
        p1 = make_shared<Player>(name);
        p2 = make_shared<Robot>();
        p3 = make_shared<Robot>();
        p4 = make_shared<Robot>();
    }

    // Inizializza il tabellone
    GameBoard gameBoard = GameBoard(p1, p2, p3, p4);
    gameBoard.show();

    // Inizia il ciclo di gioco
    play(gameBoard);

    // Fine
    return 0;
}
