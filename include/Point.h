#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point
{
    public:

        Point();
        Point(short pos_x, short pos_y);

        static Point GET_ORIGIN() { return ORIGIN; }
        static void SET_ORIGIN(Point val) { ORIGIN = val; }

        short pos_x() const { return m_pos_x; }
        short pos_y() const { return m_pos_y; }

        std::string to_string() const;


    private:

        static Point ORIGIN;

        short m_pos_x; // in m
        short m_pos_y; // in m
};

bool operator==(Point const& point1, Point const& point2);
std::ostream& operator<<(std::ostream &flux, Point const& point);

// Manhattan distance
long distance(Point const& point1, Point const& point2);

#endif // POINT_H
