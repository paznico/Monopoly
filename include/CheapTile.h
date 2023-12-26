#ifndef CHEAPTILE_H
#define CHEAPTILE_H

#include "Tile.h"

class CheapTile : public Tile 
{
    private:
        const int level_0 = 6;         // Cost buy property
        const int level_1 = 3;          // Cost upgrade to house
        const int level_2 = 3;          // Cost upgrade to hotel

        const int sleep_1 = 2;          // Cost sleeping in house
        const int sleep_2 = 4;          // Cost sleeping in hotel

    public:
        CheapTile(void);
        CheapTile(CheapTile&);
        CheapTile(CheapTile&&);

        void buy_property(const Player&) override;
        void build_house(const Player&) override;
        void build_hotel(const Player&) override;
};

#endif