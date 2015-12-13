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
    int x;
    int y;
    Coordinate(int x = -1, int y = -1);
    Coordinate& operator=(const Coordinate& a);
    Coordinate operator+(const Coordinate& a) const;
    bool operator==(const Coordinate& a) const;
    bool operator<(const Coordinate& a) const;
    bool isValid();
    std::string getRelativity(const Coordinate& coordinate);

};


#endif //WUMPUS_COORDINATE_H
