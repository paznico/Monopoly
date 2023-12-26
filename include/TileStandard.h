#ifndef STANDARDTILE_H
#define STANDARDTILE_H

#include "Tile.h"

class StandardTile : public Tile 
{
    private:
        const int level_0 = 10;         // Cost buy property
        const int level_1 = 5;          // Cost upgrade to house
        const int level_2 = 5;          // Cost upgrade to hotel

        const int sleep_1 = 4;          // Cost sleeping in house
        const int sleep_2 = 8;          // Cost sleeping in hotel

    public:
        StandardTile(void);
        StandardTile(StandardTile&);
        StandardTile(StandardTile&&);

        void buy_property(const Player&) override;
        void build_house(const Player&) override;
        void build_hotel(const Player&) override;
};

#endif