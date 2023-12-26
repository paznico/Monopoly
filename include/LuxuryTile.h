#ifndef LUXURYTILE_H
#define LUXURYTILE_H

#include "Tile.h"

class LuxuryTile : public Tile 
{
    private:
        const int level_0 = 20;         // Cost buy property
        const int level_1 = 10;         // Cost upgrade to house
        const int level_2 = 10;          // Cost upgrade to hotel

        const int sleep_1 = 7;          // Cost sleeping in house
        const int sleep_2 = 14;         // Cost sleeping in hotel

    public:
        LuxuryTile(void);
        LuxuryTile(LuxuryTile&);
        LuxuryTile(LuxuryTile&&);

        void buy_property(const Player&) override;
        void build_house(const Player&) override;
        void build_hotel(const Player&) override;
};

#endif