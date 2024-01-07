/*
 * Autore file: Davide Saladino
 */
#include "../include/GameBoard.h"

#include <ctime>
#include <stdlib.h>
#include <iostream>

/*
 * ------------------- GameBoard implementation ---------------------
 * TODO: - implement copy constructor and move constructor
 *       - handle angular tiles properly ( almost done. I created an AngularTile enum class )
 *       - save player position
 *       - show() only prints the tiles ( add the players and their houses/hotels) (1.5 Visualizzazione)
 * -------------------------------------------------------------------
 */

/*
* In this implementation, we employ srand() with the current time as the seed to generate random numbers. 
* Without this seeding, the sequence of numbers produced by rand() would remain constant across program runs. 
* If the reliability of the program is significantly contingent on the unpredictability of these numbers, 
* this could introduce a security vulnerability. A player might forecast the sequence and leverage this 
* knowledge for personal gain. However, given that the game remains unaffected by a player's awareness of 
* the number sequence, this approach is considered safe and suitable for our purposes.
*/

GameBoard::GameBoard(void)
{
    this->generate_tiles();
}

void GameBoard::increment_player_pos(const int player, const int pos)
{
    this->playersPos[player] += (pos % 28);
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
    int pos = this->playersPos[this->current_player()];
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
            // Pay the rent to the owner
            if(status == 1) {}
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

        if (random == 0)
            tiles[x] = std::make_unique<Tile<AngularTile>>();
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