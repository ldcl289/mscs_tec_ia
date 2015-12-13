//
// Created by lchavarr on 12/13/15.
//

#ifndef WUMPUS_COORDINATE_H
#define WUMPUS_COORDINATE_H

#include <string>

class Coordinate
{
public:
    const static std::string north;
    const static std::string east;
    const static std::string south;
    const static std::string west;
    const static std::string invalid;
    static int size;

    Coordinate(const Coordinate& current);
    Coordinate(Coordinate* current);
    Coordinate(int x = -1, int y = -1);
    Coordinate& operator=(const Coordinate& a);
    Coordinate operator+(const Coordinate& a) const;
    bool operator==(const Coordinate& a) const;
    bool operator<(const Coordinate& a) const;
    bool isValid();
    std::string getReference(const Coordinate& coordinate) const;
    Coordinate getNeighborhoodByReference(const std::string& reference) const;

    int x;
    int y;
};

#endif //WUMPUS_COORDINATE_H
