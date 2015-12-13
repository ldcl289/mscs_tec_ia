//
// Created by lchavarr on 12/13/15.
//

#ifndef WUMPUS_COORDINATE_H
#define WUMPUS_COORDINATE_H

#include <string>

class Coordinate
{
public:
    static std::string north;
    static std::string east;
    static std::string south;
    static std::string west;
    static std::string invalid;

    Coordinate(const Coordinate& current);
    Coordinate(Coordinate* current);
    Coordinate(int x = -1, int y = -1);
    Coordinate& operator=(const Coordinate& a);
    Coordinate operator+(const Coordinate& a) const;
    bool operator==(const Coordinate& a) const;
    bool operator<(const Coordinate& a) const;
    bool isValid();
    std::string getRelativity(const Coordinate& coordinate);

    int x;
    int y;
};
class CoordinateComparator
{
public:
   bool operator() (const Coordinate& lhs, const Coordinate& rhs) const
   {
       return lhs.x < rhs.x && lhs.y < rhs.y;
   }
};

#endif //WUMPUS_COORDINATE_H
