/*
 * Autore file: Davide Saladino
 */
#include "../include/GameBoard.h"

/*
 * ------------------- GameBoard implementation ---------------------
 * TODO: - implement copy constructor and move constructor (?)
 *       - handle angular tiles properly ( almost done. I created an AngularTile enum class )
 *       - show() only prints the tiles ( add the players and their houses/hotels) (1.5 Visualizzazione)
 *       - the player should be able to print the Game Board
 * -------------------------------------------------------------------
 */

/*
* In this implementation, we employ srand() with the current time as the seed to generate random numbers for
* tiles generation. Without this seeding, the sequence of numbers produced by rand() would remain constant 
* across program runs.If the reliability of the program is significantly contingent on the unpredictability 
* of these numbers,this could introduce a security vulnerability. A player might forecast the sequence and 
* leverage this knowledge for personal gain. However, given that the game remains unaffected by a player's 
* awareness of the number sequence, this approach is considered safe and suitable for our purposes.
* Meanwhile, for a more secure approach, we use the C++11 random number generation library to generate
* random dice throws. 
*/

GameBoard::GameBoard(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Player> p3, std::shared_ptr<Player> p4)
{

    std::vector<std::shared_ptr<Player>> players_order = std::vector<std::shared_ptr<Player>>(4);
    find_unique({3, 2, 1, 0}, std::multimap<int, std::shared_ptr<Player>>{{dice_throw(), p1}, {dice_throw(), p2}, {dice_throw(), p3}, {dice_throw(), p4}}, players_order);

    std::cout << "Player vector ordered:" << std::endl;
    for(const auto& entry : players_order)
    {
        std::cout << "Entry: " << entry->get_name() << std::endl;\
        this->players.push(entry);
    }
    this->generate_tiles();
}

void GameBoard::find_unique(std::vector<int> pos, std::multimap<int, std::shared_ptr<Player>> players, std::vector<std::shared_ptr<Player>>& vec)
{
    if(pos.empty()) return;
    //std::cout << "Pos size: " << pos.size() << std::endl;
    // for(const auto& entry : players)
    // {
    //     std::cout << "Entry: " << entry.first << " " << entry.second->get_name() << std::endl;
    // }

    std::multimap<int, std::shared_ptr<Player>> tmp = players;

    std::string player_throw_output = "";
    std::string player_order_output = "";
    std::string player_rethrow_output = "Players: ";

    int count = 0;

    auto it = pos.begin();
    
    for(const auto& entry : players)
    {
        player_throw_output += "Player " + entry.second->get_name() + " has thrown " + std::to_string(entry.first) + "\n";

        if(players.count(entry.first) == 1)
        {
            player_order_output += "Player " + entry.second->get_name() + " is in position " + std::to_string(pos[count] +1) + "\n";
            vec[pos[count]] = entry.second;
            tmp.erase(entry.first);
            pos.erase(pos.begin() + count--);
        }
        count++;
    }

    std::cout << player_throw_output << std::endl;
    std::cout << player_order_output << std::endl;

    players.clear();

    if(!tmp.empty()) 
    {
        for(const auto& entry : tmp)
        {
            player_rethrow_output += entry.second->get_name() + " ";
            players.insert({dice_throw(), entry.second});
        }
        player_rethrow_output += "have to rethrow since they have the same number. \n";

        std::cout << player_rethrow_output << std::endl;
    }

    find_unique(pos, players, vec);
}

void GameBoard::next_turn(void)
{
    // Check if the game is finished
    if(this->players.size() == 1) {
        gameFinished = true;
        return;
    }

    // Get the player at the front of the queue
    auto p = this->players.front();
    std::cout << "Player " << p->get_name() << " is playing" << std::endl;

    const int old_player_pos = p->get_position();
    // Throw the dice
    int dice = dice_throw();
    p->move(dice);

    // Check if the player has passed the start
    if(p->get_position() < old_player_pos)
    {
        int new_balance = p->get_balance() + 20;
        p->set_balance(new_balance);
    }

    action_handler(p);

    // Move the player to the back of the queue
    this->players.pop();
    this->players.push(p);
}

int GameBoard::dice_throw(void) const
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);
    return dist6(rng) + dist6(rng);
}

void GameBoard::action_handler(std::shared_ptr<Player> p)
{
    int pos = p->get_position();
    auto tile = this->tiles[pos].get();
    int status = tile->get_status();

    char choice;

    // Different choice based on the tile type and status

    if(status == 0)
    {
        // Ask the player if he wants to buy the terrain
        std::cout << "Do you want to buy the terrain? (S/N)" << std::endl;
        std::cin >> choice;

        if(choice == 'S') 
            tile->buy_terrain(p);
            //log.add_log(p.get_name()<<" ha acquistato il terreno "<<);
    }
    else 
    {
        if(tile->get_owner() == p)
        {
            if(status == 1)
            {
                // Ask the player if he wants to build a house
                std::cout << "Do you want to build a house? (S/N)" << std::endl;
                std::cin >> choice;

                if(choice == 'S')
                    tile->build_house(p);
            }
            else if(status == 2)
            {
                // Ask the player if he wants to build an hotel
                std::cout << "Do you want to build an hotel? (S/N)" << std::endl;
                std::cin >> choice;

                if(choice == 'S')
                    tile->build_hotel(p);
            }
        }
        else
        {
            if(status == 1)
                tile->pay_rent_house(p);
            else if(status == 2)
                tile->pay_rent_hotel(p);
        }
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

        std::string tile_name = "";
        if(x <= 6)
            tile_name = "A" + char(x + 49);
        else if(x <= 13)
            tile_name = char(x + 58) + "8";
        else if(x <= 20)
           tile_name = "H" + char(70 - x);
        else
            tile_name = char(93 - x) + "1";

        if (random == 0)
            tiles[x] = std::make_unique<Tile<AngularTile>>(tile_name);
        else if (random == 1)
            tiles[x] = std::make_unique<Tile<CheapTile>>();
        else if (random == 2)
            tiles[x] = std::make_unique<Tile<StandardTile>>();
        else if (random == 3)
            tiles[x] = std::make_unique<Tile<LuxuryTile>>();
    }
}

void GameBoard::show()
{
    int n = 8;
    int k = 0;
    int l = this->tiles.size() - 1;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
            {
                // Here the logic to display correct info about the tile
                if (j == 0 && i != 0 && i != n - 1)
                    std::cout << '\t' << (char)toupper(this->tiles[l--].get()->get_type()[0]) << '\t';
                else if (i == n - 1)
                    std::cout << '\t' << (char)toupper(this->tiles[tiles.size() - (k++) + n - 1].get()->get_type()[0]) << '\t';
                else
                    std::cout << '\t' << (char)toupper(this->tiles[k++].get()->get_type()[0]) << '\t';

                if(j == n - 1)
                    std::cout << std::endl;
            }
            else
            {
                std::cout << "\t   \t";
            }
        }
        std::cout << std::endl;
    }
    
}

void GameBoard::show_property(void)
{
    auto p1 = this->players.front();
    std::string p1_property = p1->get_name() + ": ";
    this->players.pop();
    this->players.push(p1);
    auto p2 = this->players.front();
    std::string p2_property = p2->get_name() + ": ";
    this->players.pop();
    this->players.push(p2);
    auto p3 = this->players.front();
    std::string p3_property = p3->get_name() + ": ";
    this->players.pop();
    this->players.push(p3);
    auto p4 = this->players.front();
    std::string p4_property = p4->get_name() + ": ";
    this->players.pop();
    this->players.push(p4);


    for(int i = 0; i < 28; i++)
    {
        auto tile = this->tiles[i].get();
        if(tile->get_owner() == p1)
            p1_property += "COORDINATA"; //tile->get_coord();
        else if(tile->get_owner() == p2)
            p2_property += "COORDINATA";
        else if(tile->get_owner() == p3)
            p3_property += "COORDINATA";
        else
            p4_property += "COORDINATA";
    }

    std::cout<<p1_property<<"\n";
    std::cout<<p2_property<<"\n";
    std::cout<<p3_property<<"\n";
    std::cout<<p4_property<<"\n";
}
