#include "Point.h"
#include <iostream>
#include <string>
#include <sstream>

Point Point::ORIGIN = Point();

Point::Point()
    :m_pos_x(0), m_pos_y(0)
{}

Point::Point(short pos_x, short pos_y)
    :m_pos_x(pos_x), m_pos_y(pos_y)
{}

std::string Point::to_string() const
{
    std::string str;

    // Convert pox_x and pox_y to string
    std::stringstream sstream_x;
    sstream_x << m_pos_x;
    std::string x = sstream_x.str();
    std::stringstream sstream_y;
    sstream_y << m_pos_y;
    std::string y = sstream_y.str();

    str = "(" + x + ", " + y + ")";

    return str;
}

bool operator==(Point const& point1, Point const& point2)
{
    return (point1.pos_x() == point2.pos_x())
        && (point1.pos_y() == point2.pos_y());
}

std::ostream& operator<<(std::ostream &flux, Point const& point)
{
    std::cout << point.to_string();
    return flux;
}

long distance(Point const& point1, Point const& point2)
{
    return abs(point1.pos_x() - point2.pos_x()) + abs(point1.pos_y() - point2.pos_y());
}
