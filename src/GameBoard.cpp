/*
 * Autore file: Davide Saladino
 */
#include "../include/GameBoard.h"

/*
 * ------------------- GameBoard implementation ---------------------
 * TODO: - implement copy constructor and move constructor (?)
 * -------------------------------------------------------------------
 */

GameBoard::GameBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Player> p3, std::shared_ptr<Player> p4)
{
    std::vector<std::shared_ptr<Player>> players_order = std::vector<std::shared_ptr<Player>>(4);
    find_unique({3, 2, 1, 0}, std::multimap<int, std::shared_ptr<Player>>{{dice_throw(), p1}, {dice_throw(), p2}, {dice_throw(), p3}, {dice_throw(), p4}}, players_order);

    std::cout << "Ordine d'inizio:" << std::endl;
    for (const auto &entry : players_order)
    {
        std::cout << "Posizione: " << entry->get_name() << std::endl;
        this->players.push_back(entry);
    }
    this->generate_tiles();
}

void GameBoard::find_unique(std::vector<int> pos, std::multimap<int, std::shared_ptr<Player>> players, std::vector<std::shared_ptr<Player>> &vec)
{
    if (pos.empty())
        return;

    std::multimap<int, std::shared_ptr<Player>> tmp = players;

    std::string player_throw_output = "";
    std::string player_order_output = "";
    std::string player_rethrow_output = "";

    int count = 0;

    auto it = pos.begin();

    for (const auto &entry : players)
    {
        player_throw_output += entry.second->get_name() + " ha tirato " + std::to_string(entry.first) + "\n";

        if (players.count(entry.first) == 1)
        {
            player_order_output += entry.second->get_name() + " e' in posizione " + std::to_string(pos[count] + 1) + "\n";
            vec[pos[count]] = entry.second;
            tmp.erase(entry.first);
            pos.erase(pos.begin() + count--);
        }
        count++;
    }

    std::cout << player_throw_output << std::endl;
    std::cout << player_order_output << std::endl;

    players.clear();

    if (!tmp.empty())
    {
        for (const auto &entry : tmp)
        {
            player_rethrow_output += entry.second->get_name() + " ";
            players.insert({dice_throw(), entry.second});
        }
        player_rethrow_output += "devono ritirare i dadi perche' hanno ottenuto lo stesso numero. \n";

        std::cout << player_rethrow_output << std::endl;
    }

    find_unique(pos, players, vec);
}

void GameBoard::next_turn(void)
{

    for (int i = 0; i < 4; i++)
        std::cout << players.at(i)->get_name() << std::endl;

    // Check if the game is finished
    if (this->players.size() == 1)
    {
        gameFinished = true;
        return;
    }

    // Get the player at the front of the queue
    auto p = this->players.front();
    std::string str = "E' il turno di " + p->get_name() + "!";
    std::cout << str << std::endl;
    Logger::get_instance().log(str);

    const int old_player_pos = p->get_position();
    // Throw the dice
    int dice = dice_throw();
    str = p->get_name() + " ha tirato i dadi ottenendo un valore di " + std::to_string(dice);
    std::cout << str << std::endl;
    Logger::get_instance().log(str);
    p->move(dice);

    auto tile = this->tiles[p->get_position()].get();
    str = p->get_name() + " e' arrivato alla casella " + tile->get_coord();
    std::cout << str << std::endl;
    Logger::get_instance().log(str);

    // Check if the player has passed the start
    if (p->get_position() < old_player_pos)
    {
        p->add_balance(5);
        std::string str = p->get_name() + " e' passato per il via e ha ritirato 20 fiorini!";
        std::cout << str << std::endl; 
        Logger::get_instance().log(str);
    }

    action_handler(p);
    str = p->get_name() + " ha finito il turno \n";
    std::cout << str;
    Logger::get_instance().log(str);

    // Move the player to the back of the queue
    this->players.pop_front();
    this->players.push_back(p);
}

int GameBoard::dice_throw(void) const
{
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    return dice1 + dice2;
}

void GameBoard::action_handler(std::shared_ptr<Player> p)
{
    int pos = p->get_position();
    auto tile = this->tiles[pos].get();
    int status = tile->get_status();

    char choice;
    bool end_turn = false;

    while (!end_turn)
    {
        // Check if it's an angular tile
        if(tile->get_type() == " ")
        {
            end_turn = true;
        }

         // Different choice based on the tile type and status
        if ((status == 0) && (end_turn == false))
        {
            // Ask the player if he wants to buy the terrain
            std::cout << "Vuoi comprare il terreno? (S/N/M <Si/No/Mostra tabellone>)" << std::endl;
            std::cin >> choice;

            if (choice == 'S')
                tile->buy_terrain(p);
        }
        else if(end_turn == false)
        {
            if (tile->get_owner() == p)
            {
                if (status == 1)
                {
                    // Ask the player if he wants to build a house
                    std::cout << "Vuoi costruire una casa? (S/N/M <Si/No/Mostra tabellone>)" << std::endl;
                    std::cin >> choice;

                    if (choice == 'S')
                        tile->build_house(p);
                }
                else if (status == 2)
                {
                    // Ask the player if he wants to build an hotel
                    std::cout << "Vuoi migliorare la casa in hotel? (S/N/M <Si/No/Mostra tabellone>)" << std::endl;
                    std::cin >> choice;

                    if (choice == 'S')
                        tile->build_hotel(p);
                }
                else if (status == 3)
                    end_turn = true;
            }
            else
            {
                if (status == 2)
                    tile->pay_rent_house(p);
                else if (status == 3)
                    tile->pay_rent_hotel(p);
                end_turn = true;
            }
        }

        if (choice == 'M')
        {
            std::cout << "Tabellone:" << std::endl;
            this->show();
        }
        else if (choice == 'S' || choice == 'N')
            end_turn = true;
    }
}

void GameBoard::generate_tiles(void)
{
    srand(time(NULL));
    int max_cheap = 8, max_standard = 10, max_luxury = 6;

    for (int x = 0; x < tiles.size(); x++)
    {
        int random = 0; // 0= angular, 1 = cheap, 2 = standard, 3 = luxury
        do
        {
            if (x % 7 != 0)
            {
                random = rand() % 3 + 1;

                switch (random)
                {
                case 1:
                    if (max_cheap == 0)
                        random = -1;
                    else
                        max_cheap--;
                    break;
                case 2:
                    if (max_standard == 0)
                        random = -1;
                    else
                        max_standard--;
                    break;
                case 3:
                    if (max_luxury == 0)
                        random = -1;
                    else
                        max_luxury--;
                    break;
                }
            }

        } while (random == -1 && (max_cheap != 0 || max_standard != 0 || max_luxury != 0));

        // Debugging info
        // std::cout << "Random: " << random << std::endl;
        // std::cout << "Max cheap: " << max_cheap << std::endl;
        // std::cout << "Max standard: " << max_standard << std::endl;
        // std::cout << "Max luxury: " << max_luxury << std::endl;

        std::string tile_coord = "";
        if (x <= 6)
        {
            tile_coord = "A";
            tile_coord += (char(x + 49));
        }
        else if (x <= 13)
        {
            tile_coord = (char(x + 58));
            tile_coord += "8";
        }
        else if (x <= 20)
        {
            tile_coord = "H";
            tile_coord += (char(70 - x));
        }
        else
        {
            tile_coord = char(93 - x);
            tile_coord += "1";
        }

        if (random == 0)
            tiles[x] = std::make_unique<Tile<AngularTile>>(tile_coord);
        else if (random == 1)
            tiles[x] = std::make_unique<Tile<CheapTile>>(tile_coord);
        else if (random == 2)
            tiles[x] = std::make_unique<Tile<StandardTile>>(tile_coord);
        else if (random == 3)
            tiles[x] = std::make_unique<Tile<LuxuryTile>>(tile_coord);
    }
}

void GameBoard::show()
{
    int n = 8;
    int k = 0;
    int l = this->tiles.size() - 1;

    std::shared_ptr<Player> p1 = this->players.at(0);
    std::shared_ptr<Player> p2 = this->players.at(1);
    std::shared_ptr<Player> p3 = this->players.at(2);
    std::shared_ptr<Player> p4 = this->players.at(3);

    // Print col coordinates A to H
    for (int i = 0; i < n; ++i)
        std::cout << "\t  " << i + 1 << "  \t";

    std::cout << std::endl
              << std::endl;

    for (int i = 0; i < n; ++i)
    {
        std::cout << char(i + 65);

        for (int j = 0; j < n; ++j)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                int index;

                if (j == 0 && i != 0 && i != n - 1)
                    index = l--;
                else if (i == n - 1)
                    index = tiles.size() - (k++) + n - 1;
                else
                    index = k++;

                std::string out = "\t| ";

                if (index == 0)
                    out = "\t| P";
                else
                    out += char(toupper(this->tiles[index].get()->get_type()[0]));

                if (this->tiles[index].get()->get_status() == 2)
                    out += "*";
                if (this->tiles[index].get()->get_status() == 3)
                    out += "^";

                if (index == p1->get_position())
                    out += p1->get_name().at(p1->get_name().size() - 1);
                if (index == p2->get_position())
                    out += p2->get_name().at(p2->get_name().size() - 1);
                if (index == p3->get_position())
                    out += p3->get_name().at(p3->get_name().size() - 1);
                if (index == p4->get_position())
                    out += p4->get_name().at(p4->get_name().size() - 1);

                out += " |\t";
                std::cout << out;

                if (j == n - 1)
                    std::cout << std::endl;
            }
            else
                std::cout << "\t   \t";
        }

        std::cout << std::endl;
    }

    std::string p1_property = p1->get_name() + ": ";
    std::string p2_property = p2->get_name() + ": ";
    std::string p3_property = p3->get_name() + ": ";
    std::string p4_property = p4->get_name() + ": ";

    for (int i = 0; i < tiles.size(); i++)
    {
        auto tile = this->tiles[i].get();
        if (tile->get_owner() == p1)
            p1_property += tile->get_coord() + " ";
        if (tile->get_owner() == p2)
            p2_property += tile->get_coord() + " ";
        if (tile->get_owner() == p3)
            p3_property += tile->get_coord() + " ";
        if (tile->get_owner() == p4)
            p4_property += tile->get_coord() + " ";
    }

    std::cout << "Proprieta' possedute giocatori:\n";
    std::cout << p1_property << "\n";
    std::cout << p2_property << "\n";
    std::cout << p3_property << "\n";
    std::cout << p4_property << "\n\n";

    std::cout << "Fiorini posseduti dai giocatori:\n";
    std::cout << *(p1.get());
    std::cout << *(p2.get());
    std::cout << *(p3.get());
    std::cout << *(p4.get()) << "\n";
}