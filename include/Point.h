#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>

class Point
{
    public:

        Point();
        Point(int pos_x, int pos_y);

        static Point GET_ORIGIN() { return ORIGIN; }
        static void SET_ORIGIN(Point val) { ORIGIN = val; }

        int pos_x() const { return m_pos_x; }
        int pos_y() const { return m_pos_y; }

        std::string to_string() const;


    private:

        static Point ORIGIN;

        int m_pos_x; // in m
        int m_pos_y; // in m
};

bool operator==(Point const& point1, Point const& point2);
std::ostream& operator<<(std::ostream &flux, Point const& point);

/**
 * Calculate the Manhattan distance between two points
 * @param point1 The first point
 * @param point2 The second point
 * @return The distance between the two points
 */
int distance(Point const& point1, Point const& point2);

#endif // POINT_H
