/*
 * Author: Davide Saladino
 */
#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
 * Define all tiles constants as part
 * of the their specific enum <Type>Tile
 */

enum class CheapTile : int
{
    COST_PROPERTY = 6,
    COST_HOUSE = 3,
    COST_HOTEL = 3,
    RENT_HOUSE = 2,
    RENT_HOTEL = 4,
};

enum class StandardTile : int
{
    COST_PROPERTY = 10,
    COST_HOUSE = 5,
    COST_HOTEL = 5,
    RENT_HOUSE = 4,
    RENT_HOTEL = 8,
};

enum class LuxuryTile : int
{
    COST_PROPERTY = 20,
    COST_HOUSE = 10,
    COST_HOTEL = 10,
    RENT_HOUSE = 7,
    RENT_HOTEL = 14,
};

enum class AngularTile : int
{
    COST_PROPERTY = 0,
    COST_HOUSE = 0,
    COST_HOTEL = 0,
    RENT_HOUSE = 0,
    RENT_HOTEL = 0,
};

#endif